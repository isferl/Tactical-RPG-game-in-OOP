#include <GameProcess/UpgradeAbilityAction.h>
#include <Robot/Player.h>
#include <Other/Constants.h>


void UpgradeAbilityAction::choose_ability_if_need(RobotPlayer &player, GameState &current_state) {
    if (player.get_point_update() <= 0 || current_state == GameState::GameOver ||
        current_state == GameState::ChoosingUpdateAbility)
        return;

    prev_game_state = current_state;
    current_state = GameState::ChoosingUpdateAbility;
}

void UpgradeAbilityAction::choosing_update_ability(Input::Action action, RobotPlayer &player,
                                                   GameState &current_state, GenerateCard &card) {
    if (player.get_point_update() <= 0)
        return;

    AbilityType type;
    switch (action) {
        case Input::Action::Num1:
            type = card.get_to_index(0);
            break;
        case Input::Action::Num2:
            type = card.get_to_index(1);
            break;
        case Input::Action::Num3:
            type = card.get_to_index(2);
            break;
        case Input::Action::Num4:
            type = card.get_to_index(3);
            break;
        default:
            return;
    }

    player.update_ability(XP_FOR_RANK_UP, type);
    card.generate_card(CARD_IN_GAME);
    if (player.get_point_update() == 0)
        current_state = prev_game_state;
}
