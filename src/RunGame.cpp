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
#include <GameProcess/HandleAction.h>
#include <GameProcess/TurnGame.h>
#include <GameProcess/ChoseCell.h>
#include <Abulity/Ability.h>
#include <GameProcess/GenerateCard.h>
#include <Other/ItemsType.h>
#include <nlohmann/json.hpp>

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

        world.get_board().get_square(2, 1).set_random_item();
        world.get_board().get_square(1, 2).set_random_item();
        world.get_board().get_square(2, 2).set_random_item();

        EndGame endgame(world.get_enemies().size(),
                        "../../material/Fond/HomeVideo-Regular.ttf");
        CoutInformation info("../../material/Fond/HomeVideo-Regular.ttf");
        sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "bin-bon");
        RenderGame Render(window);
        window.setFramerateLimit(30);
        window.setIcon(image);

        while (window.isOpen()) {
            actions.choose_ability_if_need(world.get_player(), current_state);
            Input input;
            while (const auto action = input.read(window)) {
                actions.handle_action(*action, world, moved, window, endgame, continue_game, current_state, card);
                if (!window.isOpen())
                    break;
                actions.choose_ability_if_need(world.get_player(), current_state);
            }
            if (!window.isOpen())
                break;
            Turn.update_turn(world, endgame, current_state, turn_number);
            actions.choose_ability_if_need(world.get_player(), current_state);
            window.clear();
            Render.draw_board(world);
            Render.draw_factories(world);
            Render.draw_player(world);
            Render.draw_robots(world.get_enemies(), CellType::EnemyType);
            Render.draw_robots(world.get_allies(), CellType::AllyType);
            Render.draw_invisible_cell(world);


            if (current_state == GameState::ChoosingCell) {
                Render.draw_selected_cell(actions.get_selection().get_selected(), world,
                                          *actions.get_selected_ability_type());
                Render.draw_blackout(actions.get_selection().get_radius(), world);
            }

            if (current_state == GameState::GameOver)
                endgame.draw(window);

            std::cout << "-------" << std::endl;

            std::string str;
            str += "Status\n";
            for (const auto &[type, status]:
                 world.get_player().get_statues()) {
                if (status->is_finished())
                    continue;

                switch (type) {
                    case StatusType::Burning:
                        str += "Gorenue " + std::to_string(status->get_turns()) + " ";
                        break;
                    case StatusType::Overload:
                        str += "Peregruzka " + std::to_string(status->get_turns()) + " ";
                        break;
                    case StatusType::Shield:
                        str += "Shit " + std::to_string(status->get_turns()) + " ";
                        break;
                    case StatusType::Slowdown:
                        str += "Zamedlenue " + std::to_string(status->get_turns()) + " ";
                        break;
                }
            }
            str += "\nAbility Level\n";

            for (const auto &[type, ability]:
                 world.get_player().get_ability()) {
                if (!ability->get_level())
                    continue;

                switch (type) {
                    case AbilityType::AreaDamage:
                        str += "Area " + std::to_string(ability->get_level()) + " ";
                        break;
                    case AbilityType::FairDamage:
                        str += "Fair " + std::to_string(ability->get_level()) + " ";
                        break;
                    case AbilityType::Heal:
                        str += "Heal " + std::to_string(ability->get_level()) + " ";
                        break;
                    case AbilityType::Teleports:
                        str += "Teleport " + std::to_string(ability->get_level()) + " ";
                        break;
                }
            }
            str += "\nCard\n";
            for (int i = 0; i < 4; ++i) {
                switch (card.get_to_index(i)) {
                    case AbilityType::AreaDamage:
                        str += "Area ";
                        break;
                    case AbilityType::FairDamage:
                        str += "Fair ";
                        break;
                    case AbilityType::Heal:
                        str += "Heal ";
                        break;
                    case AbilityType::Teleports:
                        str += "Teleport ";
                        break;
                }
            }
            str += "\n";
            str += "\nBackpack\n";
            for (int i = 0; i < world.get_player().get_backpack().size(); ++i) {
                switch (world.get_player().get_backpack_to_index(i).get_name()) {
                    case ItemsType::EnergyDrink:
                        str += "EnergyDrink ";
                        break;
                    case ItemsType::StrengthPotion:
                        str += "StrengthPotion ";
                        break;
                    case ItemsType::Meat:
                        str += "Meat ";
                        break;
                }
            }
            str += "\n";
            std::cout << str;
            std::cout << "-------" << std::endl;
            info.cout_hp(window, world.get_player());
            info.cout_xp(window, world.get_player());
            info.cout_stamina(window, world.get_player());
            window.display();
        }
    }
}
