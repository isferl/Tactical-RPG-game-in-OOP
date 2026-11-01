#pragma once
#include <GameProcess/EndGame.h>
#include <GameProcess/GameState.h>
#include <Robot/Robot.h>
#include <list>

class TurnGame {
public:
    void update_turn(GameWorld &world, EndGame &endgame, GameState &current_state, int &turn_number);

    template<typename Type>
    void clear_dead(std::list<Type> &robots);

    void turn_end_status(Robot &robot, GameWorld &world);

    void turn_end_ability(Robot &robot);

    void end_turn(GameWorld &world);

    void next_turn(GameWorld &world, int &turn_number);
};
