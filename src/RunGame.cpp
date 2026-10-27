#include <RunGame.h>
#include <iostream>
#include <list>
#include <GameMap/GenerateGame.h>
#include <GameMap/IncludeJson.h>
#include <GameProcess/EndGame.h>
#include <GameProcess/Moved.h>
#include <Graphics/CoutInformation.h>
#include <Graphics/Render.h>
#include <Other/Constants.h>
#include <Robot/Ally.h>
#include <Robot/Player.h>

void RunGame::launch_window() {
    sf::Image image;
    if (!image.loadFromFile("../../material/Other/game_icon.png")) {
        std::cerr << "Не удалось загрузить изображение!" << std::endl;
        return;
    }
    bool continue_game = true;
    while (continue_game) {
        current_state = GameState::WaitingForPlayerInput;
        turn_number = 0;

        IncludeJson Json;
        LevelConfig config = Json.load("game.json");

        GameWorld world(config);
        GenerateGame generate_game;
        generate_game.create(world, config);
        Moved moved;

        world.get_player().get_area_damage().add_xp(10);

        EndGame endgame(world.get_enemies().size(),
                        "../../material/Fond/HomeVideo-Regular.ttf");
        CoutInformation info("../../material/Fond/HomeVideo-Regular.ttf");
        sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "bin-bon");
        RenderGame Render(window);
        window.setFramerateLimit(30);
        window.setIcon(image);

        while (window.isOpen()) {
            Input input;
            while (const auto action = input.read(window)) {
                handle_action(*action, world, moved, window, endgame, continue_game);
                if (!window.isOpen())
                    break;
            }
            if (!window.isOpen())
                break;
            update_turn(world, endgame);
            window.clear();
            Render.draw_board(world);
            Render.draw_factories(world);
            Render.draw_player(world);
            Render.draw_robots(world.get_enemies(), -2);
            Render.draw_robots(world.get_allies(), 2);
            Render.draw_invisible_cell(world);
            if (current_state == GameState::GameOver)
                endgame.draw(window);


            // for (const auto &[type, status]:
            //      world.get_player().get_statues()) {
            //     if (status->is_finished())
            //         continue;
            //
            //     switch (type) {
            //         case StatusType::Burning:
            //             std::cout << "Gorenue " << status->get_turns() << " ";
            //             break;
            //         case StatusType::Overload:
            //             std::cout << "Peregruzka " << status->get_turns() << " ";
            //             break;
            //         case StatusType::Shield:
            //             std::cout << "Shit " << status->get_turns() << " ";
            //             break;
            //         case StatusType::Slowdown:
            //             std::cout << "Zamedlenue " << status->get_turns() << " ";
            //             break;
            //     }
            // }
            //
            // std::cout << '\n';


            info.cout_hp(window, world.get_player());
            info.cout_xp(window, world.get_player());
            info.cout_stamina(window, world.get_player());
            window.display();
        }
    }
}

void RunGame::handle_action(Input::Action action, GameWorld &world, Moved &moved, sf::RenderWindow &window,
                            EndGame &endgame, bool &continue_game) {
    if (action == Input::Action::Close) {
        continue_game = false;
        window.close();
        return;
    }
    if (action == Input::Action::UseAreaDamage) {
        world.get_player().get_area_damage().use_ability(world.get_player(), world, 0, 0);
        return;
    }
    if (action == Input::Action::Restart) {
        window.close();
        return;
    }

    if (current_state == GameState::GameOver) {
        if (action == Input::Action::Confirm || action == Input::Action::Cancel) {
            continue_game = false;
            window.close();
        }
        return;
    }
    if (current_state != GameState::WaitingForPlayerInput ||
        check_game_over(world, endgame))
        return;
    if (action == Input::Action::EndTurn) {
        current_state = GameState::EnemiesMoving;
        return;
    }
    std::optional<Moved::Direction> direction;
    switch (action) {
        case Input::Action::MoveLeft: direction = Moved::Direction::Left;
            break;
        case Input::Action::MoveRight: direction = Moved::Direction::Right;
            break;
        case Input::Action::MoveUp: direction = Moved::Direction::Up;
            break;
        case Input::Action::MoveDown: direction = Moved::Direction::Down;
            break;
        default: return;
    }
    if (moved.player_move(world, *direction)) {
        if (check_game_over(world, endgame))
            return;
        if (world.get_player().get_stamina() <= 0)
            current_state = GameState::EnemiesMoving;
    }
}

bool RunGame::check_game_over(GameWorld &world, EndGame &endgame) {
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

void RunGame::update_turn(GameWorld &world, EndGame &endgame) {
    if (current_state == GameState::GameOver || check_game_over(world, endgame))
        return;
    if (current_state == GameState::EnemiesMoving) {
        end_turn(world);
        if (check_game_over(world, endgame))
            return;
        current_state = GameState::TurnComplete;
    }
    if (current_state == GameState::TurnComplete) {
        for (auto &factory: world.get_factories()) {
            factory.tick();
            if (factory.should_spawn())
                factory.try_spawn_enemy(world.get_board(), world.get_map(), world.get_enemies());
        }
        next_turn(world);
        current_state = GameState::WaitingForPlayerInput;
        check_game_over(world, endgame);
    }
}

void RunGame::clear_dead(std::list<Robot> &robots) {
    auto iterations = robots.cbegin();
    while (iterations != robots.cend()) {
        if (iterations->get_statis_live()) {
            ++iterations;
            continue;
        }
        iterations = robots.erase(iterations);
    }
}

void RunGame::turn_end_status(Robot &robot, GameWorld &world) {
    for (auto &[type, status]: robot.get_statues()) {
        if (!status->is_finished()) {
            status->on_turn_end(robot);
            if (!robot.get_statis_live()) {
                world.clear_full_cell(robot.get_position_on_map_x(), robot.get_position_on_map_y());
                return;
            }
        }
    }
}

void RunGame::end_turn(GameWorld &world) {
    Moved moved;
    for (auto &ally: world.get_allies()) {
        if (!world.get_player().get_statis_live())
            return;
        if (ally.get_statis_live()) {
            moved.entity_turn(ally, world, 2);
        }
    }
    for (auto &enemy: world.get_enemies()) {
        if (!world.get_player().get_statis_live())
            return;
        if (enemy.get_statis_live()) {
            moved.entity_turn(enemy, world, -2);
        }
    }
}

void RunGame::next_turn(GameWorld &world) {
    ++turn_number;
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
}
