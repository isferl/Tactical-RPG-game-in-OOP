#include <GameProcess/AbilityAction.h>
#include <GameMap/GameWorld.h>
#include <Abulity/Ability.h>

bool AbilityAction::handle_action(Input::Action action, GameWorld &world, GameState &current_state) {
    RobotPlayer &player = world.get_player();
    Ability *ability = nullptr;
    bool choose_cell = false;

    switch (action) {
        case Input::Action::UseAreaDamage:
            ability = &player.get_area_damage();
            break;
        case Input::Action::UseHeal:
            ability = &player.get_heal_ability();
            break;
        case Input::Action::UseFairDamage:
            ability = &player.get_fair_damage();
            choose_cell = true;
            break;
        case Input::Action::UseTeleports:
            ability = &player.get_teleports();
            choose_cell = true;
            break;
        default:
            return false;
    }

    if (!ability->is_ready())
        return true;

    if (!player.get_overload().use_effect(player, ability->get_energy_cost()))
        return true;

    if (!choose_cell) {
        ability->use_ability(player, world, {0, 0});
        return true;
    }

    if (player.get_stamina() < ability->get_energy_cost())
        return true;

    selection.start({player.get_position_on_game_x(), player.get_position_on_game_y()},
                    ability->get_radius(), world.get_board().get_width(), world.get_board().get_height());
    selected_ability = ability;
    current_state = GameState::ChoosingCell;
    return true;
}

void AbilityAction::choosing_cell(Input::Action action, GameWorld &world, GameState &current_state) {
    if (action == Input::Action::Cancel) {
        selected_ability = nullptr;
        current_state = GameState::WaitingForPlayerInput;
        return;
    }

    auto point = selection.chose_to_player(action);
    if (!point || selected_ability == nullptr)
        return;

    int x = point->first, y = point->second;
    const Square &cell = world.get_board().get_square(x, y);

    if (selected_ability->get_name() == AbilityType::FairDamage && cell.get_type() != CellType::EnemyType)
        return;

    if (selected_ability->get_name() == AbilityType::Teleports && (
            cell.get_type() != CellType::EmptyType || cell.get_impassable()))
        return;

    Ability *ability = selected_ability;
    selected_ability = nullptr;
    current_state = GameState::WaitingForPlayerInput;
    ability->use_ability(world.get_player(), world, {x, y});
}

const ChoseCell &AbilityAction::get_selection() const {
    return selection;
}

std::optional<AbilityType> AbilityAction::get_selected_ability_type() const {
    if (selected_ability == nullptr)
        return std::nullopt;
    return selected_ability->get_name();
}
