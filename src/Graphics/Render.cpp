#include <Graphics/Render.h>
#include <iostream>
#include <list>
#include <GameMap/GenerateBoard.h>
#include <Robot/Player.h>
#include <Other/Constants.h>
#include <Other/NeedFunction.h>

RenderGame::RenderGame(sf::RenderWindow &window) : window(window) {
    if (!texture_for_cell_easy.loadFromFile("../../material/Board/cell_normal.png")) {
        std::cerr << "Не удалось загрузить изображение!" << std::endl;
        return;
    }
    if (!texture_for_cell_medium.loadFromFile("../../material/Board/cell_medium.png")) {
        std::cerr << "Не удалось загрузить изображение!" << std::endl;
        return;
    }
    if (!texture_for_cell_hard.loadFromFile("../../material/Board/cell_hard.png")) {
        std::cerr << "Не удалось загрузить изображение!" << std::endl;
        return;
    }
    if (!texture_for_cell_invisible_for_easy.loadFromFile("../../material/Board/cell_hidden_normal.png")) {
        std::cerr << "Не удалось загрузить изображение!" << std::endl;
        return;
    }
    if (!texture_for_cell_invisible_for_medium.loadFromFile("../../material/Board/cell_hidden_medium.png")) {
        std::cerr << "Не удалось загрузить изображение!" << std::endl;
        return;
    }
    if (!texture_for_cell_invisible_for_hard.loadFromFile("../../material/Board/cell_hidden_hard.png")) {
        std::cerr << "Не удалось загрузить изображение!" << std::endl;
        return;
    }
    if (!texture_for_wall.loadFromFile("../../material/Board/cell_wall.png")) {
        std::cerr << "Не удалось загрузить изображение!" << std::endl;
        return;
    }
    if (!texture_for_factory.loadFromFile("../../material/Board/factory.png")) {
        std::cerr << "Не удалось загрузить изображение!" << std::endl;
        return;
    }
    if (!robot_player.loadFromFile("../../material/Robots/robot_player.png")) {
        std::cerr << "Не удалось загрузить изображение!" << std::endl;
        return;
    }
    if (!robot_ally.loadFromFile("../../material/Robots/robot_ally.png")) {
        std::cerr << "Не удалось загрузить изображение!" << std::endl;
        return;
    }
    if (!robot_enemy.loadFromFile("../../material/Robots/robot_enemy.png")) {
        std::cerr << "Не удалось загрузить изображение!" << std::endl;
        return;
    }
}

void RenderGame::draw_player(GameWorld &world) const {
    sf::RectangleShape player;
    player.setSize(sf::Vector2f(CEIL_SIZE, CEIL_SIZE));
    player.setTexture(&robot_player);
    player.setOrigin(sf::Vector2f(CEIL_SIZE / 2.0, CEIL_SIZE / 2.0));
    player.setPosition(get_center(world.get_player().get_position_on_map_x(),
                                  world.get_player().get_position_on_map_y()));
    window.draw(player);
}

void RenderGame::draw_square(const int x, const int y, const sf::Texture &texture) const {
    sf::RectangleShape square;
    square.setSize(sf::Vector2f(CEIL_SIZE, CEIL_SIZE));
    square.setPosition(get_coordinates_cell(x, y));
    square.setTexture(&texture);
    window.draw(square);
}

void RenderGame::draw_robot(const Robot &robot, int type) const {
    if (!robot.get_statis_live()) {
        return;
    }
    sf::RectangleShape robot_draw;
    robot_draw.setSize(sf::Vector2f(CEIL_SIZE, CEIL_SIZE));
    if (type == 2)
        robot_draw.setTexture(&robot_ally);
    else
        robot_draw.setTexture(&robot_enemy);
    robot_draw.setOrigin(sf::Vector2f(CEIL_SIZE / 2.0, CEIL_SIZE / 2.0));
    robot_draw.setPosition(get_center(robot.get_position_on_map_x(), robot.get_position_on_map_y()));
    window.draw(robot_draw);
}


void RenderGame::draw_board(GameWorld &world) const {
    int x_map = world.get_board().get_width() + 2;
    int y_map = world.get_board().get_height() + 2;
    for (int x = 0; x < x_map; ++x) {
        for (int y = 0; y < y_map; ++y) {
            if (world.get_board().get_square(x, y).get_impassable())
                draw_square(x, y, texture_for_wall);
            else if (world.get_board().get_square(x, y).get_cost_cell() == STAMINA_FOR_EASY_CELL)
                draw_square(x, y, texture_for_cell_easy);
            else if (world.get_board().get_square(x, y).get_cost_cell() == STAMINA_FOR_MEDIUM_CELL)
                draw_square(x, y, texture_for_cell_medium);
            else if (world.get_board().get_square(x, y).get_cost_cell() == STAMINA_FOR_HARD_CELL)
                draw_square(x, y, texture_for_cell_hard);
        }
    }
}


void RenderGame::draw_robots(const std::list<Robot> &robots, int type) const {
    for (const auto &robot: robots)
        draw_robot(robot, type);
}

void RenderGame::draw_factory(const RobotFactory &factory) const {
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

void RenderGame::draw_factories(GameWorld &world) const {
    for (const auto &factory: world.get_factories())
        draw_factory(factory);
}

void RenderGame::draw_invisible_cell(GameWorld &world) const {
    int x_map = world.get_board().get_width() + 2;
    int y_map = world.get_board().get_height() + 2;
    int x_player = world.get_player().get_position_on_map_x();
    int y_player = world.get_player().get_position_on_map_y();
    for (int y = 0; y < y_map; ++y) {
        for (int x = 0; x < x_map; ++x) {
            if (NeedFunction::distance(x_player, y_player, x, y) > world.get_player().get_visibility_distance())
                if (not((world.get_board().get_field()[y][x].get_impassable() || world.get_board().get_field()[y][x].
                         get_motionless()) && world.get_board().get_field()[y][x].get_visibility())) {
                    if (world.get_board().get_field()[y][x].get_cost_cell() == STAMINA_FOR_MEDIUM_CELL && world.
                        get_board().get_field()[y][x].
                        get_visibility())
                        draw_square(x, y, texture_for_cell_invisible_for_medium);
                    else if (world.get_board().get_field()[y][x].get_cost_cell() == STAMINA_FOR_HARD_CELL && world.
                             get_board().get_field()[y][x]
                             .get_visibility())
                        draw_square(x, y, texture_for_cell_invisible_for_hard);
                    else
                        draw_square(x, y, texture_for_cell_invisible_for_easy);
                }
            if (NeedFunction::distance(x_player, y_player, x, y) <= world.get_player().get_visibility_distance())
                world.get_board().get_field()[y][x].set_visibility(true);
        }
    }
}

sf::Vector2f RenderGame::get_center(const int x, const int y) const {
    return {OFFSET_X + CEIL_SIZE * x + CEIL_SIZE / 2, OFFSET_Y + CEIL_SIZE * y + CEIL_SIZE / 2};
}

sf::Vector2f RenderGame::get_coordinates_cell(const int x, const int y) const {
    return {OFFSET_X + CEIL_SIZE * x, OFFSET_Y + CEIL_SIZE * y};
}
