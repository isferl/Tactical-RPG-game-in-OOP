#pragma once
#include <GameMap/GameWorld.h>
#include <Robot/Player.h>

class Moved {
public:
    enum class Direction { Left, Right, Up, Down };

    bool player_moved(GameWorld &world, int x, int y);

    bool player_move(GameWorld &world, Direction direction);

    bool entities_moving(Robot &robot, GameWorld &world, int x, int y, int robot_type);

    bool entities_move(Robot &robot, GameWorld &world, int robot_type);

    void entity_turn(Robot &robot, GameWorld &world, int robot_type);
};
