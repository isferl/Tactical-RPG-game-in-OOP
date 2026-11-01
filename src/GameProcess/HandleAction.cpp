#include <GameProcess/HandleAction.h>
#include <GameMap/GameWorld.h>
#include <Other/Direction.h>

void HandleAction::handle_action(Input::Action action, GameWorld &world, Moved &moved, sf::RenderWindow &window,
                                 EndGame &endgame, bool &continue_game, GameState &current_state, GenerateCard &card) {
    if (action == Input::Action::Close) {
        continue_game = false;
        window.close();
        return;
    }
    if (action == Input::Action::Restart) {
        window.close();
        return;
    }
    if (current_state == GameState::ChoosingCell) {
        ability_action.choosing_cell(action, world, current_state);
        if (current_state == GameState::WaitingForPlayerInput)
            finish_action(world, endgame, current_state);
        return;
    }
    if (current_state == GameState::ChoosingUpdateAbility) {
        upgrade_ability_action.choosing_update_ability(action, world.get_player(), current_state, card);
        return;
    }
    if (current_state == GameState::GameOver) {
        if (action == Input::Action::Confirm || action == Input::Action::Cancel) {
            continue_game = false;
            window.close();
        }
        return;
    }
    if (current_state != GameState::WaitingForPlayerInput || check_game_over(world, endgame, current_state))
        return;

    if (ability_action.handle_action(action, world, current_state)) {
        if (current_state == GameState::WaitingForPlayerInput)
            finish_action(world, endgame, current_state);
        return;
    }
    if (action == Input::Action::EndTurn) {
        current_state = GameState::EnemiesMoving;
        return;
    }

    if (action == Input::Action::Num1 || action == Input::Action::Num2 || action == Input::Action::Num3 || action ==
        Input::Action::Num4) {
        use_item_from_backpack(world.get_player(), action);
        return;
    }

    moving(action, world, moved, endgame, current_state);
}

void HandleAction::moving(Input::Action action, GameWorld &world, Moved &moved,
                          EndGame &endgame, GameState &current_state) {
    std::optional<Direction> direction;
    switch (action) {
        case Input::Action::MoveLeft:
            direction = Direction::Left;
            break;
        case Input::Action::MoveRight:
            direction = Direction::Right;
            break;
        case Input::Action::MoveUp:
            direction = Direction::Up;
            break;
        case Input::Action::MoveDown:
            direction = Direction::Down;
            break;
        default:
            return;
    }
    if (moved.player_move(world, *direction))
        finish_action(world, endgame, current_state);
}

void HandleAction::finish_action(GameWorld &world, EndGame &endgame, GameState &current_state) const {
    if (check_game_over(world, endgame, current_state))
        return;
    check_player_stamina(world, current_state);
}

bool HandleAction::check_game_over(GameWorld &world, EndGame &endgame, GameState &current_state) {
    int alive_enemies = 0;
    for (const auto &enemy: world.get_enemies())
        if (enemy.get_statis_live())
            ++alive_enemies;

    endgame.set_count_enemy(alive_enemies);
    endgame.set_player_alive(world.get_player().get_statis_live());
    if (!world.get_player().get_statis_live() || alive_enemies == 0) {
        current_state = GameState::GameOver;
        return true;
    }
    return false;
}

const ChoseCell &HandleAction::get_selection() const {
    return ability_action.get_selection();
}

std::optional<AbilityType> HandleAction::get_selected_ability_type() const {
    return ability_action.get_selected_ability_type();
}

void HandleAction::check_player_stamina(GameWorld &world, GameState &current_state) const {
    if (world.get_player().get_stamina() <= 0)
        current_state = GameState::EnemiesMoving;
}

void HandleAction::choose_ability_if_need(RobotPlayer &player, GameState &current_state) {
    upgrade_ability_action.choose_ability_if_need(player, current_state);
}

void HandleAction::use_item_from_backpack(RobotPlayer &player, Input::Action action) {
    switch (action) {
        case Input::Action::Num1:
            player.use_item_to_index(0);
            return;
        case Input::Action::Num2:
            player.use_item_to_index(1);
            return;
        case Input::Action::Num3:
            player.use_item_to_index(2);
            return;
        case Input::Action::Num4:
            player.use_item_to_index(3);
            return;
    }
}
