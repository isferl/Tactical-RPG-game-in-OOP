#pragma once
#include <GameMap/FullMap.h>
#include <GameMap/GameWorld.h>
#include <GameMap/GenerateBoard.h>

class GenerateGame {
public:
    void set_cost_cell(Board &board, std::pair<int, int> dot, int cost_cell);

    void set_wall(FullMap &map, Board &board, std::pair<int, int> dot);

    void set_factory(FullMap &map, Board &board, std::pair<int, int> dot);

    void place_robot(Robot &robot, FullMap &map, Board &board, std::pair<int, int> dot, int type);

    void create(GameWorld &world, LevelConfig &config);

    static void set_random_status_for_random_cell(GameWorld &world);
};
