#include "../include/Moved.h"
#include "../include/Interactions.h"
#include "../include/NeedFunction.h"

bool Moved::player_moved(RobotPlayer &player, Board &board, FullMap &map, int x, int y) {
    if (!player.get_statis_live())
        return false;
    int odd_x = player.get_position_on_map_x();
    int odd_y = player.get_position_on_map_y();
    bool flag = false;

    if (map.get_map_in_xy(x, y) == 0) {
        if (!player.try_spend_stamina(board.get_field()[y][x].get_cost_cell())) {
            return false;
        }
        player.set_position_on_map_xy(x, y);
        board.get_field()[y][x].set_type_cell(1, map, x, y);
        map.set_map_in_xy(odd_x, odd_y, 0);
        board.get_field()[y][x].set_robot(&player);
        board.get_field()[odd_y][odd_x].clear_cell();
        flag = true;
    }
    if (map.get_map_in_xy(x, y) == -2 || map.get_map_in_xy(x, y) == 2) {
        Interactions interaction;
        if (!player.try_spend_stamina(board.get_field()[y][x].get_cost_cell())) {
            return false;
        }
        if (interaction.interactions(board.get_field()[odd_y][odd_x], board.get_field()[y][x])) {
            player.update_xp(board.get_field()[y][x].get_robot()->get_xp_for_kill());
            map.set_map_in_xy(x, y, 0);
            board.get_field()[y][x].clear_cell();
        }
        flag = true;
    }
    return flag;
}

bool Moved::player_move(Board &board, RobotPlayer &player, FullMap &map, Direction direction) {
    int x = player.get_position_on_map_x();
    int y = player.get_position_on_map_y();
    switch (direction) {
        case Direction::Left: return player_moved(player, board, map, x - 1, y);
        case Direction::Right: return player_moved(player, board, map, x + 1, y);
        case Direction::Up: return player_moved(player, board, map, x, y - 1);
        case Direction::Down: return player_moved(player, board, map, x, y + 1);
    }
    return false;
}

bool Moved::entities_moving(Robot &robot, Board &board, FullMap &map, int x, int y, int robot_type) {
    int odd_x = robot.get_position_on_map_x();
    int odd_y = robot.get_position_on_map_y();
    Interactions interaction;
    bool flag = false;

    if (map.get_map_in_xy(x, y) == 0) {
        int cost = board.get_field()[y][x].get_cost_cell();
        if (!robot.try_spend_stamina(cost)) {
            return false;
        }
        robot.set_position_on_map_x(x);
        robot.set_position_on_map_y(y);
        board.get_field()[y][x].set_type_cell(robot_type, map, x, y);
        map.set_map_in_xy(odd_x, odd_y, 0);
        board.get_field()[y][x].set_robot(&robot);
        board.get_field()[odd_y][odd_x].clear_cell();
        flag = true;
    } else if (map.get_map_in_xy(x, y) == 1 || map.get_map_in_xy(x, y) == 2 || map.get_map_in_xy(x, y) == -2) {
        int cost = board.get_field()[y][x].get_cost_cell();
        if (!robot.try_spend_stamina(cost)) {
            return false;
        }
        if (interaction.interactions(board.get_field()[odd_y][odd_x], board.get_field()[y][x])) {
            map.set_map_in_xy(x, y, 0);
            board.get_field()[y][x].clear_cell();
        }
        flag = true;
    }
    return flag;
}


bool Moved::entities_move(Robot &robot, Board &board, FullMap &map, int robot_type) {
    int x = robot.get_position_on_map_x();
    int y = robot.get_position_on_map_y();
    int key = get_random_number(1, 4);
    switch (key) {
        case 1:
            return entities_moving(robot, board, map, x - 1, y, robot_type);

        case 2:
            return entities_moving(robot, board, map, x + 1, y, robot_type);

        case 3:
            return entities_moving(robot, board, map, x, y - 1, robot_type);

        case 4:
            return entities_moving(robot, board, map, x, y + 1, robot_type);

        default:
            return false;
    }
}


void Moved::entity_turn(Robot &robot, Board &board, FullMap &map, int robot_type) {
    while (robot.get_statis_live() && robot.get_stamina() > 0) {
        int stamina_before = robot.get_stamina();
        entities_move(robot, board, map, robot_type);

        if (robot.get_stamina() == stamina_before)
            break;
    }
}
