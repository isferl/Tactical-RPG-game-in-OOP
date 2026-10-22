#pragma once
#include <vector>
#include "GenerateBoard.h"
#include "FullMap.h"

class RobotFactory {
protected:
    int position_x;
    int position_y;
    int spawn_interval;
    int turns_counter = 0;
    bool is_alive = true;

public:
    RobotFactory(int x, int y, int spawn_interval);

    int get_position_x() const;

    int get_position_y() const;

    int get_spawn_interval() const;

    int get_turns_counter() const;

    bool get_statis_live() const;


    bool should_spawn() const;

    void tick();

    bool try_spawn_enemy(Board &board, FullMap &map, std::vector<Robot> &enemies);
};
