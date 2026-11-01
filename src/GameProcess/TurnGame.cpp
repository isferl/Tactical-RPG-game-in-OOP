#include <GameProcess/TurnGame.h>
#include <GameMap/GenerateGame.h>
#include <GameProcess/HandleAction.h>

void TurnGame::update_turn(GameWorld &world, EndGame &endgame, GameState &current_state, int &turn_number) {
    if (current_state == GameState::GameOver || HandleAction::check_game_over(world, endgame, current_state))
        return;
    if (current_state == GameState::EnemiesMoving) {
        end_turn(world);
        if (HandleAction::check_game_over(world, endgame, current_state))
            return;
        current_state = GameState::TurnComplete;
    }
    if (current_state == GameState::TurnComplete) {
        for (auto &factory: world.get_factories()) {
            factory.tick();
            if (factory.should_spawn())
                factory.try_spawn_enemy(world.get_board(), world.get_enemies());
        }
        next_turn(world, turn_number);
        current_state = GameState::WaitingForPlayerInput;
        HandleAction::check_game_over(world, endgame, current_state);
    }
}

template<typename Type>
void TurnGame::clear_dead(std::list<Type> &robots) {
    auto iterations = robots.cbegin();
    while (iterations != robots.cend()) {
        if (iterations->get_statis_live()) {
            ++iterations;
            continue;
        }
        iterations = robots.erase(iterations);
    }
}

void TurnGame::turn_end_status(Robot &robot, GameWorld &world) {
    for (auto &[type, status]: robot.get_statues()) {
        if (!status->is_finished()) {
            status->on_turn_end(robot);
            if (!robot.get_statis_live()) {
                world.clear_full_cell(robot.get_position_on_game_x(), robot.get_position_on_game_y());
                return;
            }
        }
    }
}

void TurnGame::turn_end_ability(Robot &robot) {
    for (auto &[type, ability]: robot.get_ability())
        ability->on_turn_end();
}

void TurnGame::end_turn(GameWorld &world) {
    Moved moved;
    for (auto &ally: world.get_allies()) {
        if (!world.get_player().get_statis_live())
            return;
        if (ally.get_statis_live()) {
            moved.entity_turn(ally, world, CellType::AllyType);
        }
    }
    for (auto &enemy: world.get_enemies()) {
        if (!world.get_player().get_statis_live())
            return;
        if (enemy.get_statis_live()) {
            moved.entity_turn(enemy, world, CellType::EnemyType);
        }
    }
}

void TurnGame::next_turn(GameWorld &world, int &turn_number) {
    ++turn_number;
    turn_end_ability(world.get_player());
    for (auto &ally: world.get_allies())
        turn_end_ability(ally);
    for (auto &enemy: world.get_enemies())
        turn_end_ability(enemy);

    world.get_player().turn_end_item();
    bool flag = false;
    turn_end_status(world.get_player(), world);
    if (world.get_player().get_statis_live())
        world.get_player().restore_stamina(STAMINA_RESTORED_PER_TURN);
    for (auto &ally: world.get_allies())
        if (ally.get_statis_live()) {
            ally.restore_stamina(STAMINA_RESTORED_PER_TURN);
            turn_end_status(ally, world);
        } else
            flag = true;
    for (auto &enemy: world.get_enemies())
        if (enemy.get_statis_live()) {
            enemy.restore_stamina(STAMINA_RESTORED_PER_TURN);
            turn_end_status(enemy, world);
        } else
            flag = true;
    if (flag) {
        clear_dead(world.get_enemies());
        clear_dead(world.get_allies());
    }
    for (int i = 0; i < COUNT_STATUS_FOR_TURN; ++i) {
        GenerateGame::set_random_status_for_random_cell(world);
    }
    for (int i = 0; i < COUNT_ITEMS_FOR_TURN; ++i) {
        GenerateGame::set_random_items_for_random_cell(world);
    }
}
