#include <GameMap/GameWorld.h>
#include <GameProcess/Interactions.h>
#include <GameProcess/Moved.h>
#include <Other/NeedFunction.h>
#include <IntelligenceRobots/IntelligenceRobots.h>

bool Moved::player_move(GameWorld &world, Direction direction) {
    int x = world.get_player().get_position_on_game_x();
    int y = world.get_player().get_position_on_game_y();
    std::pair<int, int> move_to = move(direction);
    if (move_to.first != 0 || move_to.second != 0)
        return moving(world.get_player(), world, {x + move_to.first, y + move_to.second}, CellType::PlayerType);
    return false;
}

std::pair<int, int> Moved::move(Direction direction) {
    switch (direction) {
        case Direction::Left: return {-1, 0};
        case Direction::Right: return {1, 0};
        case Direction::Up: return {0, -1};
        case Direction::Down: return {0, 1};
    }
    return {0, 0};
}

bool Moved::moving(Robot &robot, GameWorld &world, std::pair<int, int> dot, CellType robot_type) {
    int x = dot.first;
    int y = dot.second;
    int odd_x = robot.get_position_on_game_x();
    int odd_y = robot.get_position_on_game_y();
    Interactions interaction;
    bool flag = false;

    if (world.get_board().get_type_in_xy(x, y) == CellType::EmptyType) {
        if (!robot.get_slowdown().use_effect(robot, 0))
            return false;
        if (!robot.try_spend_stamina(world.get_board().get_field()[y][x].get_cost_cell())) {
            return false;
        }
        robot.set_position_on_game_x(x);
        robot.set_position_on_game_y(y);
        world.get_board().get_field()[y][x].set_type_cell(robot_type);
        world.get_board().get_field()[y][x].set_robot(&robot);
        world.clear_full_cell(odd_x, odd_y);
        if (robot_type == CellType::PlayerType)
            world.get_player().pick_up_item(world);
        flag = true;
    } else if (world.get_board().get_type_in_xy(x, y) == CellType::PlayerType || world.get_board().get_type_in_xy(x, y)
               ==
               CellType::AllyType || world.get_board().get_type_in_xy(x, y) == CellType::EnemyType) {
        if (!robot.try_spend_stamina(world.get_board().get_field()[y][x].get_cost_cell())) {
            return false;
        }
        if (interaction.interactions(world.get_board().get_field()[odd_y][odd_x],
                                     world.get_board().get_field()[y][x])) {
            world.clear_full_cell(x, y);
        }
        flag = true;
    }
    return flag;
}

bool Moved::entities_move(Entities &robot, GameWorld &world, CellType robot_type) {
    int x = robot.get_position_on_game_x();
    int y = robot.get_position_on_game_y();
    int key = NeedFunction::get_random_number(1, 4);
    switch (key) {
        case 1:
            --x;
            break;
        case 2:
            ++x;
            break;
        case 3:
            --y;
            break;
        case 4:
            ++y;
            break;
        default:
            return false;
    }
    return moving(robot, world, {x, y}, robot_type);
}


bool Moved::entities_move(Entities &robot, GameWorld &world, std::pair<int, int> dot, CellType robot_type) {
    if (dot.first < 1 || dot.second < 1 || dot.first > world.get_board().get_width() ||
        dot.second > world.get_board().get_height())
        return false;
    if (NeedFunction::distance(robot.get_position_on_game_x(), robot.get_position_on_game_y(),
                               dot.first, dot.second) != 1)
        return false;
    Square &cell = world.get_board().get_square(dot.first, dot.second);
    if (cell.get_impassable() || cell.get_motionless())
        return false;
    return moving(robot, world, dot, robot_type);
}

void Moved::entity_turn(Entities &robot, GameWorld &world, CellType) {
    IntelligenceRobots intelligence(robot, world);
    while (robot.get_statis_live() && robot.get_stamina() > 0) {
        int stamina_before = robot.get_stamina();
        if (!intelligence.main_intelligence() || intelligence.is_turn_finished())
            break;

        if (robot.get_stamina() == stamina_before)
            break;
    }
}
