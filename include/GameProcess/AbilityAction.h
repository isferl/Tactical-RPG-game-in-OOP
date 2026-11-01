#pragma once
#include <GameProcess/ChoseCell.h>
#include <GameProcess/GameState.h>
#include <Other/AbilityType.h>

class GameWorld;
class Ability;

class AbilityAction {
private:
    ChoseCell selection;
    Ability *selected_ability = nullptr;

public:
    bool handle_action(Input::Action action, GameWorld &world, GameState &current_state);

    void choosing_cell(Input::Action action, GameWorld &world, GameState &current_state);

    const ChoseCell &get_selection() const;

    std::optional<AbilityType> get_selected_ability_type() const;
};
