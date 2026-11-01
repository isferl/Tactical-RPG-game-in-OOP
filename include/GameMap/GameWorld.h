#pragma once
#include <list>
#include <Robot/FactoryRobot.h>
#include <GameMap/GenerateBoard.h>
#include <GameMap/LevelConfig.h>
#include <Robot/Ally.h>
#include <Robot/Enemy.h>
#include <Robot/Player.h>

class GameWorld {
private:
    Board board;
    RobotPlayer player;
    std::list<Ally> allies;
    std::list<Enemy> enemies;
    std::list<RobotFactory> factories;

public:
    GameWorld(LevelConfig &config);

    Board &get_board();

    RobotPlayer &get_player();

    std::list<Ally> &get_allies();

    std::list<Enemy> &get_enemies();

    std::list<RobotFactory> &get_factories();

    void clear_full_cell(int x, int y);
};
