#pragma once
#include <GameProcess/GameState.h>

class RunGame {
protected:
    GameState current_state = GameState::WaitingForPlayerInput;
    int turn_number = 0;

public:
    void launch_window();
};
