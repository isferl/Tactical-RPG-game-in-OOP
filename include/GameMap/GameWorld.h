#pragma once
#include <list>
#include <Robot/FactoryRobot.h>
#include <GameMap/GenerateBoard.h>
#include <GameMap/LevelConfig.h>

class GameWorld {
private:
    FullMap map;
    Board board;
    RobotPlayer player;

    std::list<Robot> allies;
    std::list<Robot> enemies;
    std::list<RobotFactory> factories;

public:
    GameWorld(LevelConfig &config);

    FullMap &get_map();

    Board &get_board();

    RobotPlayer &get_player();

    std::list<Robot> &get_allies();

    std::list<Robot> &get_enemies();

    std::list<RobotFactory> &get_factories();

    void clear_full_cell(int x, int y);

    void clear_full_cell();
};
