#include "../include/RunGame.h"
#include <iostream>
#include "../include/Constants.h"
#include "../include/FullMap.h"
#include "../include/Player.h"
#include "../include/Ally.h"
#include "../include/GenerateBoard.h"
#include "../include/GenerateGame.h"
#include "../include/Render.h"
#include "../include/Moved.h"
#include "../include/EndGame.h"
#include "../include/CapacityReservation.h"
#include "../include/CoutInformation.h"

void RunGame::launch_window() {
    sf::Image image;
    if (!image.loadFromFile("../../material/Other/img.png")) {
        std::cerr << "Не удалось загрузить изображение!" << std::endl;
        return;
    }
    GenerateGame generate_game;
    FullMap Map(BOARD_HEIGHT, BOARD_WIDTH);
    Board Board(Map, STAMINA_FOR_EASY_CELL);
    RobotPlayer Player(HEAL, MAX_HP, DAMAGE, MAX_STAMINA, 1, 1, 1);
    std::vector<Robot> allies;
    RobotFactory factory(7, 7, 5);
    std::vector<Robot> enemies;
    std::vector<RobotFactory> factories;
    CapacityReservation capacity_reservation;
    std::vector<std::pair<int, int> > coordinate_ally;
    std::vector<std::pair<int, int> > coordinate_enemy;
    allies.reserve(5);
    enemies.reserve(100);
    factories.reserve(2);
    Player.take_damage(50);
    factories.push_back(factory);
    Moved moved;
    generate_game.full_board(Board, {3, 3}, {5, 5}, STAMINA_FOR_MEDIUM_CELL);
    generate_game.full_board(Board, {7, 3}, {9, 5}, STAMINA_FOR_HARD_CELL);
    generate_game.set_wall(Map, Board, {2, 7}, {5, 8});
    generate_game.set_player(Player, Map, Board, {1, 1});
    generate_game.set_factory(Map, Board, {7, 7});
    generate_game.set_entities(allies, coordinate_ally, capacity_reservation, Map, Board, {2, 6}, {5, 7}, 2, 0);
    generate_game.set_entities(enemies, coordinate_enemy, capacity_reservation, Map, Board, {2, 8}, {5, 9}, -2, 30);
    EndGame endgame(static_cast<int>(enemies.size()),
                    "../../material/Fond/HomeVideo-Regular.ttf");
    CoutInformation info("../../material/Fond/HomeVideo-Regular.ttf");
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "bin-bon");
    RenderGame Render(window);
    window.setFramerateLimit(60);
    window.setIcon(image);

    Input input;
    while (window.isOpen()) {
        while (const auto action = input.read(window)) {
            handle_action(*action, Board, Player, Map, moved, window, enemies, endgame);
            if (!window.isOpen())
                break;
        }
        if (!window.isOpen())
            break;
        update_turn(Board, Player, Map, allies, enemies, factories, endgame);
        window.clear();
        Render.draw(Board, Map);
        Render.draw(factories);
        Render.draw(Player, Map);
        for (auto &enemy: enemies)
            Render.draw(enemy, Map, sf::Color(255, 0, 0));
        for (auto &ally: allies)
            Render.draw(ally, Map, sf::Color(255, 165, 0));
        Render.draw_invisible_cell(Board, Player, Map);
        if (current_state == GameState::GameOver)
            endgame.draw(window);
        info.cout_hp(window, Player);
        info.cout_xp(window, Player);
        info.cout_stamina(window, Player);
        window.display();
    }
}

void RunGame::handle_action(Input::Action action, Board &board, RobotPlayer &player,
                            FullMap &map, Moved &moved, sf::RenderWindow &window,
                            const std::vector<Robot> &enemies, EndGame &endgame) {
    if (action == Input::Action::Close) {
        window.close();
        return;
    }
    if (current_state == GameState::GameOver) {
        if (action == Input::Action::Confirm || action == Input::Action::Cancel)
            window.close();
        return;
    }
    if (current_state != GameState::WaitingForPlayerInput ||
        check_game_over(player, enemies, endgame))
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
    if (moved.player_move(board, player, map, *direction)) {
        if (check_game_over(player, enemies, endgame))
            return;
        if (player.get_stamina() <= 0)
            current_state = GameState::EnemiesMoving;
    }
}

bool RunGame::check_game_over(const RobotPlayer &player,
                              const std::vector<Robot> &enemies, EndGame &endgame) {
    int alive_enemies = 0;
    for (const auto &enemy: enemies)
        if (enemy.get_statis_live())
            ++alive_enemies;
    endgame.set_count_enemy(alive_enemies);
    endgame.set_player_alive(player.get_statis_live());
    if (!player.get_statis_live() || alive_enemies == 0) {
        current_state = GameState::GameOver;
        return true;
    }
    return false;
}

void RunGame::update_turn(Board &board, RobotPlayer &player, FullMap &map,
                          std::vector<Robot> &allies, std::vector<Robot> &enemies,
                          std::vector<RobotFactory> &factories, EndGame &endgame) {
    if (current_state == GameState::GameOver || check_game_over(player, enemies, endgame))
        return;
    if (current_state == GameState::EnemiesMoving) {
        end_turn(board, player, map, allies, enemies);
        if (check_game_over(player, enemies, endgame))
            return;
        current_state = GameState::TurnComplete;
    }
    if (current_state == GameState::TurnComplete) {
        for (auto &factory: factories) {
            factory.tick();
            if (factory.should_spawn())
                factory.try_spawn_enemy(board, map, enemies);
        }
        next_turn(player, allies, enemies);
        current_state = GameState::WaitingForPlayerInput;
        check_game_over(player, enemies, endgame);
    }
}

void RunGame::end_turn(Board &board, RobotPlayer &player, FullMap &map,
                       std::vector<Robot> &allies, std::vector<Robot> &enemies) {
    Moved moved;
    for (auto &enemy: enemies) {
        if (!player.get_statis_live())
            return;
        if (enemy.get_statis_live())
            moved.entity_turn(enemy, board, map, -2);
    }
    for (auto &ally: allies) {
        if (!player.get_statis_live())
            return;
        if (ally.get_statis_live())
            moved.entity_turn(ally, board, map, 2);
    }
}

void RunGame::next_turn(RobotPlayer &player, std::vector<Robot> &allies,
                        std::vector<Robot> &enemies) {
    ++turn_number;
    if (player.get_statis_live())
        player.restore_stamina(STAMINA_RESTORED_PER_TURN);
    for (auto &ally: allies)
        if (ally.get_statis_live())
            ally.restore_stamina(STAMINA_RESTORED_PER_TURN);
    for (auto &enemy: enemies)
        if (enemy.get_statis_live())
            enemy.restore_stamina(STAMINA_RESTORED_PER_TURN);
}
