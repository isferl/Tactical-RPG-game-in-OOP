#pragma once
#include <GameProcess/GameState.h>
#include <Other/Input.h>
#include <GameProcess/GenerateCard.h>

class RobotPlayer;

class UpgradeAbilityAction {
private:
    GameState prev_game_state = GameState::WaitingForPlayerInput;

public:
    void choose_ability_if_need(RobotPlayer &player, GameState &current_state);

    void choosing_update_ability(Input::Action action, RobotPlayer &player, GameState &current_state,
                                 GenerateCard &card);
};
