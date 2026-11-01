#pragma once
#include <GameProcess/AbilityAction.h>
#include <GameProcess/UpgradeAbilityAction.h>
#include <GameProcess/EndGame.h>
#include <GameProcess/Moved.h>
#include <GameProcess/GenerateCard.h>

class HandleAction {
private:
    AbilityAction ability_action;
    UpgradeAbilityAction upgrade_ability_action;

    void moving(Input::Action action, GameWorld &world, Moved &moved, EndGame &endgame, GameState &current_state);

    void finish_action(GameWorld &world, EndGame &endgame, GameState &current_state) const;

public:
    void handle_action(Input::Action action, GameWorld &world, Moved &moved, sf::RenderWindow &window, EndGame &endgame,
                       bool &continue_game, GameState &current_state, GenerateCard &card);

    static bool check_game_over(GameWorld &world, EndGame &endgame, GameState &current_state);

    const ChoseCell &get_selection() const;

    std::optional<AbilityType> get_selected_ability_type() const;

    void check_player_stamina(GameWorld &world, GameState &current_state) const;

    void choose_ability_if_need(RobotPlayer &player, GameState &current_state);

    void use_item_from_backpack(RobotPlayer &player, Input::Action action);
};
