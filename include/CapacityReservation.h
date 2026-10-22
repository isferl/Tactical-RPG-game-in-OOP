#pragma once
#include <vector>

#include "../include/GenerateBoard.h"
#include "../include/FullMap.h"

class CapacityReservation {
public:
    void spawn_entities(Board &board, FullMap &map, std::vector<Robot> &robot, int count_robots, int type_robot,
                        bool is_friend, std::vector<std::pair<int, int>> &coordinate, int xp_for_kill);
};
