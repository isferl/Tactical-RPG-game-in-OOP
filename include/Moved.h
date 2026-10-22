#pragma once
#include "GenerateBoard.h"
#include "Player.h"

class Moved {
public:
    enum class Direction { Left, Right, Up, Down };

    bool player_moved(RobotPlayer &player, Board &board, FullMap &map, int x, int y);

    bool player_move(Board &board, RobotPlayer &player, FullMap &map, Direction direction);

    bool entities_moving(Robot &robot, Board &board, FullMap &map, int x, int y, int robot_type);

    bool entities_move(Robot &robot, Board &board, FullMap &map, int robot_type);

    void entity_turn(Robot &robot, Board &board, FullMap &map, int robot_type);
};
