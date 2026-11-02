#include <RunGame.h>
#include <iostream>
#include <GameMap/GenerateGame.h>
#include <GameMap/IncludeJson.h>
#include <GameProcess/EndGame.h>
#include <GameProcess/Moved.h>
#include <Graphics/Render.h>
#include <Other/Constants.h>
#include <GameProcess/HandleAction.h>
#include <GameProcess/TurnGame.h>
#include <GameProcess/GenerateCard.h>

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
        LevelConfig config = IncludeJson::load("game.json");
        GameWorld world(config);
        GenerateGame generate_game;
        generate_game.create(world, config);

        Moved moved;
        TurnGame Turn;
        HandleAction actions;
        GenerateCard card;
        // world.get_player().update_xp(10000);
        EndGame endgame(world.get_enemies().size(),
                        "../../material/Fond/HomeVideo-Regular.ttf");
        sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "bin-bon");
        RenderGame Render(window);
        window.setFramerateLimit(30);
        window.setIcon(image);

        while (window.isOpen()) {
            actions.choose_ability_if_need(world.get_player(), current_state);
            Input input;
            while (const auto action = input.read(window)) {
                if (*action == Input::Action::ChangeDisplayMode) {
                    Render.change_display_mode();
                    continue;
                }
                actions.handle_action(*action, world, moved, window, endgame, continue_game, current_state, card);
                if (!window.isOpen())
                    break;
                actions.choose_ability_if_need(world.get_player(), current_state);
            }
            if (!window.isOpen())
                break;
            Turn.update_turn(world, endgame, current_state, turn_number);
            actions.choose_ability_if_need(world.get_player(), current_state);
            Render.draw_all(world, current_state, actions, endgame, card);
        }
    }
}
