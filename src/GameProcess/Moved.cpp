#include <GameMap/GameWorld.h>
#include <GameProcess/Interactions.h>
#include <GameProcess/Moved.h>
#include <Other/NeedFunction.h>
bool Moved::player_moved(GameWorld &world, int x, int y) {
    if (!world.get_player().get_statis_live())
        return false;
    int odd_x = world.get_player().get_position_on_map_x();
    int odd_y = world.get_player().get_position_on_map_y();
    bool flag = false;

    if (world.get_map().get_map_in_xy(x, y) == 0) {
        if (!world.get_player().get_slowdown().use_effect(world.get_player(), 0))
            return false;
        if (!world.get_player().try_spend_stamina(world.get_board().get_field()[y][x].get_cost_cell())) {
            return false;
        }
        world.get_player().set_position_on_map_xy(x, y);
        world.get_board().get_field()[y][x].set_type_cell(1, world.get_map(), x, y);
        world.get_board().get_field()[y][x].set_robot(&world.get_player());
        world.clear_full_cell(odd_x, odd_y);
        flag = true;
    }
    if (world.get_map().get_map_in_xy(x, y) == -2 || world.get_map().get_map_in_xy(x, y) == 2) {
        Interactions interaction;
        if (!world.get_player().try_spend_stamina(world.get_board().get_field()[y][x].get_cost_cell())) {
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

bool Moved::player_move(GameWorld &world, Direction direction) {
    int x = world.get_player().get_position_on_map_x();
    int y = world.get_player().get_position_on_map_y();
    switch (direction) {
        case Direction::Left: return player_moved(world, x - 1, y);
        case Direction::Right: return player_moved(world, x + 1, y);
        case Direction::Up: return player_moved(world, x, y - 1);
        case Direction::Down: return player_moved(world, x, y + 1);
    }
    return false;
}

bool Moved::entities_moving(Robot &robot, GameWorld &world, int x, int y, int robot_type) {
    int odd_x = robot.get_position_on_map_x();
    int odd_y = robot.get_position_on_map_y();
    Interactions interaction;
    bool flag = false;

    if (world.get_map().get_map_in_xy(x, y) == 0) {
        if (!robot.get_slowdown().use_effect(robot, 0))
            return false;
        if (!robot.try_spend_stamina(world.get_board().get_field()[y][x].get_cost_cell())) {
            return false;
        }
        robot.set_position_on_map_x(x);
        robot.set_position_on_map_y(y);
        world.get_board().get_field()[y][x].set_type_cell(robot_type, world.get_map(), x, y);
        world.get_board().get_field()[y][x].set_robot(&robot);
        world.clear_full_cell(odd_x, odd_y);
        flag = true;
    } else if (world.get_map().get_map_in_xy(x, y) == 1 || world.get_map().get_map_in_xy(x, y) == 2 || world.get_map().
               get_map_in_xy(x, y) == -2) {
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


bool Moved::entities_move(Robot &robot, GameWorld &world, int robot_type) {
    int x = robot.get_position_on_map_x();
    int y = robot.get_position_on_map_y();
    int key = NeedFunction::get_random_number(1, 4);
    switch (key) {
        case 1:
            return entities_moving(robot, world, x - 1, y, robot_type);

        case 2:
            return entities_moving(robot, world, x + 1, y, robot_type);

        case 3:
            return entities_moving(robot, world, x, y - 1, robot_type);

        case 4:
            return entities_moving(robot, world, x, y + 1, robot_type);

        default:
            return false;
    }
}


void Moved::entity_turn(Robot &robot, GameWorld &world, int robot_type) {
    while (robot.get_statis_live() && robot.get_stamina() > 0) {
        int stamina_before = robot.get_stamina();
        entities_move(robot, world, robot_type);

        if (robot.get_stamina() == stamina_before)
            break;
    }
}