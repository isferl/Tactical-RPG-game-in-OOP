#include "../include/Render.h"
#include <iostream>
#include "../include/GenerateBoard.h"
#include "../include/Player.h"
#include "../include/Constants.h"
#include "../include/NeedFunction.h"

RenderGame::RenderGame(sf::RenderWindow &window) : window(window) {
    if (!texture_for_cell_easy.loadFromFile("../../material/Board/Ячейка.png")) {
        std::cerr << "Не удалось загрузить изображение!" << std::endl;
        return;
    }
    if (!texture_for_cell_medium.loadFromFile("../../material/Board/Ячейка_средняя сложность.png")) {
        std::cerr << "Не удалось загрузить изображение!" << std::endl;
        return;
    }
    if (!texture_for_cell_hard.loadFromFile("../../material/Board/Ячейка_сложная_сложность.png")) {
        std::cerr << "Не удалось загрузить изображение!" << std::endl;
        return;
    }
    if (!texture_for_cell_invisible_for_easy.loadFromFile("../../material/Board/Ячейка скрытая.png")) {
        std::cerr << "Не удалось загрузить изображение!" << std::endl;
        return;
    }
    if (!texture_for_cell_invisible_for_medium.loadFromFile("../../material/Board/Ячейка скрытая средняя сложность.png")) {
        std::cerr << "Не удалось загрузить изображение!" << std::endl;
        return;
    }
    if (!texture_for_cell_invisible_for_hard.loadFromFile("../../material/Board/Ячейка скрытая сложная сложность.png")) {
        std::cerr << "Не удалось загрузить изображение!" << std::endl;
        return;
    }
    if (!texture_for_wall.loadFromFile("../../material/Board/Стена.png")) {
        std::cerr << "Не удалось загрузить изображение!" << std::endl;
        return;
    }
    if (!texture_for_factory.loadFromFile("../../material/Board/Завод.png")) {
        std::cerr << "Не удалось загрузить изображение!" << std::endl;
        return;
    }
}

void RenderGame::draw(const Board &board, FullMap &map) const {
    int x_map = board.get_width() + 2;
    int y_map = board.get_height() + 2;
    for (int x = 0; x < x_map; ++x) {
        for (int y = 0; y < y_map; ++y) {
            if (board.get_square(x, y).get_impassable())
                draw(map, x, y, texture_for_wall);
            else if (board.get_square(x, y).get_cost_cell() == STAMINA_FOR_EASY_CELL)
                draw(map, x, y, texture_for_cell_easy);
            else if (board.get_square(x, y).get_cost_cell() == STAMINA_FOR_MEDIUM_CELL)
                draw(map, x, y, texture_for_cell_medium);
            else if (board.get_square(x, y).get_cost_cell() == STAMINA_FOR_HARD_CELL)
                draw(map, x, y, texture_for_cell_hard);
        }
    }
}

void RenderGame::draw(const FullMap &map, const int x, const int y, const sf::Texture &texture) const {
    sf::RectangleShape square;
    square.setSize(sf::Vector2f(CEIL_SIZE, CEIL_SIZE));
    square.setPosition(get_coordinates_cell(x, y));
    square.setTexture(&texture);
    window.draw(square);
}

void RenderGame::draw(const RobotPlayer &player_robot, const FullMap &map) const {
    sf::CircleShape player;
    player.setRadius(ROBOT_RADIUS);
    player.setFillColor(sf::Color(0, 255, 0));
    player.setOrigin(sf::Vector2f(ROBOT_RADIUS, ROBOT_RADIUS));
    player.setPosition(get_center(player_robot.get_position_on_map_x(), player_robot.get_position_on_map_y()));
    window.draw(player);
}


void RenderGame::draw(const Robot &robot, const FullMap &map, const sf::Color color) const {
    if (!robot.get_statis_live()) {
        return;
    }
    sf::CircleShape robot_draw;
    robot_draw.setRadius(ROBOT_RADIUS);
    robot_draw.setFillColor(color);
    robot_draw.setOrigin(sf::Vector2f(ROBOT_RADIUS, ROBOT_RADIUS));
    robot_draw.setPosition(get_center(robot.get_position_on_map_x(), robot.get_position_on_map_y()));
    window.draw(robot_draw);
}



void RenderGame::draw_invisible_cell(Board &board, const RobotPlayer &player_robot, const FullMap &map) const {
    int x_map = board.get_width() + 2;
    int y_map = board.get_height() + 2;
    int x_player = player_robot.get_position_on_map_x();
    int y_player = player_robot.get_position_on_map_y();
    for (int y = 0; y < y_map; ++y) {
        for (int x = 0; x < x_map; ++x) {
            if (distance(x_player, y_player, x, y) > player_robot.get_visibility_distance())
                if (not((board.get_field()[y][x].get_impassable() || board.get_field()[y][x].get_motionless()) && board.get_field()[y][x].get_visibility())) {

                    if (board.get_field()[y][x].get_cost_cell() == STAMINA_FOR_MEDIUM_CELL && board.get_field()[y][x].get_visibility())
                        draw(map, x, y, texture_for_cell_invisible_for_medium);
                    else if (board.get_field()[y][x].get_cost_cell() == STAMINA_FOR_HARD_CELL && board.get_field()[y][x].get_visibility())
                        draw(map, x, y, texture_for_cell_invisible_for_hard);
                    else
                        draw(map, x, y, texture_for_cell_invisible_for_easy);
                }
            if (distance(x_player, y_player, x, y) <= player_robot.get_visibility_distance())
                board.get_field()[y][x].set_visibility(true);
        }
    }
}

sf::Vector2f RenderGame::get_center(const int x, const int y) const {
    return {OFFSET_X + CEIL_SIZE * x + CEIL_SIZE / 2, OFFSET_Y + CEIL_SIZE * y + CEIL_SIZE / 2};
}

sf::Vector2f RenderGame::get_coordinates_cell(const int x, const int y) const {
    return {OFFSET_X + CEIL_SIZE * x, OFFSET_Y + CEIL_SIZE * y};
}


void RenderGame::draw(const std::vector<Robot> &robots, sf::Color color, FullMap &map) const {
    for (const auto &robot: robots)
        draw(robot, map, color);
}

void RenderGame::draw(const RobotFactory &factory) const {
    if (!factory.get_statis_live()) return;

    sf::Sprite sprite(texture_for_factory);
    float target_w = FACTORY_X * CEIL_SIZE;
    float target_h = FACTORY_Y * CEIL_SIZE;
    sf::Vector2u tex_size = texture_for_factory.getSize();
    if (tex_size.x > 0 && tex_size.y > 0)
        sprite.setScale(sf::Vector2f(target_w / tex_size.x, target_h / tex_size.y));

    sprite.setPosition(sf::Vector2f(
        CEIL_SIZE * factory.get_position_x() + OFFSET_X,
        CEIL_SIZE * factory.get_position_y() + OFFSET_Y));

    window.draw(sprite);
}

void RenderGame::draw(const std::vector<RobotFactory> &factories) const {
    for (const auto &f: factories)
        draw(f);
}
