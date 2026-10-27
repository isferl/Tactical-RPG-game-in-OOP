#pragma once
#include <list>
#include <Robot/Player.h>
#include <GameMap/GameWorld.h>
#include <GameProcess/GameState.h>
#include <Other/Input.h>
#include <GameProcess/Moved.h>
#include <GameProcess/EndGame.h>

class RunGame {
protected:
    GameState current_state = GameState::WaitingForPlayerInput;
    int turn_number = 0;

    void handle_action(Input::Action action, GameWorld &world, Moved &moved, sf::RenderWindow &window, EndGame &endgame,
                       bool &continue_game);

    bool check_game_over(GameWorld &world, EndGame &endgame);

    void update_turn(GameWorld &world, EndGame &endgame);

    void clear_dead(std::list<Robot> &robots);

    void turn_end_status(Robot &robot, GameWorld &world);

public:
    void launch_window();

    void end_turn(GameWorld &world);

    void next_turn(GameWorld &world);
};
