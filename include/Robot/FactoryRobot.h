#pragma once
#include <list>
#include <GameMap/GenerateBoard.h>
#include <Robot/Enemy.h>

class RobotFactory {
private:
    int position_x;
    int position_y;
    int spawn_interval;
    int turns_counter = 0;
    int count_to_spawn;
    bool is_alive = true;

public:
    RobotFactory(int x, int y, int spawn_interval, int count_to_spawn);

    int get_position_x() const;

    int get_position_y() const;

    int get_spawn_interval() const;

    int get_turns_counter() const;

    bool get_statis_live() const;


    bool should_spawn() const;

    void tick();

    bool try_spawn_enemy(Board &board, std::list<Enemy> &enemies);
};
