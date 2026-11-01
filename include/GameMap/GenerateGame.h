#pragma once
#include <GameMap/GameWorld.h>
#include <GameMap/GenerateBoard.h>
#include <Other/CostCell.h>

class GenerateGame {
public:
    void set_cost_cell(Board &board, std::pair<int, int> dot, CostCell cost_cell);

    void set_wall(Board &board, std::pair<int, int> dot);

    void set_factory(Board &board, std::pair<int, int> dot);

    void place_robot(Robot &robot, Board &board, std::pair<int, int> dot, CellType type);

    void create(GameWorld &world, LevelConfig &config);

    static void set_random_status_for_random_cell(GameWorld &world);

    static void set_random_items_for_random_cell(GameWorld &world);
};
