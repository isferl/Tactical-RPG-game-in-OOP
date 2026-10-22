#include "../include/GenerateGame.h"

#include <cmath>


void GenerateGame::full_board(Board &board, std::pair<int, int> start, std::pair<int, int> end, int cost_cell) {
    for (int y = start.second; y < end.second; ++y)
        for (int x = start.first; x < end.first; ++x)
            board.get_field()[y][x].set_cost_cell(cost_cell);
}

void GenerateGame::set_wall(FullMap &map, Board &board, std::pair<int, int> start, std::pair<int, int> end) {
    for (int y = start.second; y < end.second; ++y)
        for (int x = start.first; x < end.first; ++x) {
            board.get_field()[y][x].set_impassable(true);
            map.set_map_in_xy(x, y, -1);
        }
}

void GenerateGame::set_player(RobotPlayer &player, FullMap &map, Board &board, std::pair<int, int> dot) {
    board.get_field()[dot.second][dot.first].set_type_cell(1, map, dot.first, dot.second);
    board.get_field()[dot.second][dot.first].set_robot(&player);
}

void GenerateGame::set_factory(FullMap &map, Board &board, std::pair<int, int> dot) {
    for (int y = 0; y < FACTORY_X; ++y)
        for (int x = 0; x < FACTORY_Y; ++x) {
            board.get_field()[7 + y][7 + x].set_type_cell(-3, map, x + dot.first, y + dot.second);
            board.get_field()[7 + y][7 + x].set_motionless(true);
        }
}

void GenerateGame::set_entities(std::vector<Robot> &robot, std::vector<std::pair<int, int>> &coordinate, CapacityReservation &capacity_reservation,
                                FullMap &map, Board &board, std::pair<int, int> start, std::pair<int, int> end, int type, int xp_for_kill) {
    for (int y = start.second; y < end.second; ++y) {
        for (int x = start.first; x < end.first; ++x) {
            std::pair<int, int> coordinates {x, y};
            coordinate.push_back(coordinates);
        }
    }
    capacity_reservation.spawn_entities(board, map, robot, abs(end.first - start.first) * abs(end.second - start.second), type, type > 0, coordinate, xp_for_kill);
}











