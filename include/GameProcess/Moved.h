#pragma once
#include <Robot/Player.h>
#include <Other/CellType.h>
#include <Other/Direction.h>
#include <Robot/Entities.h>

class Moved {
private:
    bool moving(Robot &robot, GameWorld &world, std::pair<int, int> dot, CellType robot_type);

    std::pair<int, int> move(Direction direction);

public:
    bool player_move(GameWorld &world, Direction direction);

    bool entities_move(Entities &robot, GameWorld &world, CellType robot_type);

    bool entities_move(Entities &robot, GameWorld &world, std::pair<int, int> dot, CellType robot_type);

    void entity_turn(Entities &robot, GameWorld &world, CellType robot_type);
};
