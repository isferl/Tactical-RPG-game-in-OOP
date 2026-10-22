#pragma once
#include "CapacityReservation.h"
#include "FullMap.h"
#include "GenerateBoard.h"

class GenerateGame {
public:
    void full_board(Board &board, std::pair<int, int> start, std::pair<int, int> end, int cost_cell);

    void set_wall(FullMap &map, Board &board, std::pair<int, int> start, std::pair<int, int> end);

    void set_player(RobotPlayer &player, FullMap &map, Board &board, std::pair<int, int> dot);

    void set_factory(FullMap &map, Board &board, std::pair<int, int> dot);

    void set_entities(std::vector<Robot> &robot, std::vector<std::pair<int, int> > &coordinate,
                      CapacityReservation &capacity_reservation, FullMap &map, Board &board, std::pair<int, int> start,
                      std::pair<int, int> end, int type, int xp_for_kill);
};
