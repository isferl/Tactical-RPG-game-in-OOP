#pragma once
#include <list>
#include <GameMap/GameWorld.h>
#include <Robot/FactoryRobot.h>
#include <SFML/Graphics.hpp>

class RenderGame {
protected:
    sf::RenderWindow &window;
    sf::Texture texture_for_cell_easy;
    sf::Texture texture_for_cell_medium;
    sf::Texture texture_for_cell_hard;
    sf::Texture texture_for_wall;
    sf::Texture texture_for_cell_invisible_for_easy;
    sf::Texture texture_for_cell_invisible_for_medium;
    sf::Texture texture_for_cell_invisible_for_hard;
    sf::Texture texture_for_factory;
    sf::Texture robot_player;
    sf::Texture robot_ally;
    sf::Texture robot_enemy;

public:
    RenderGame(sf::RenderWindow &window);

    void draw_player(GameWorld &world) const;

    void draw_square(int x, int y, const sf::Texture &texture) const;

    void draw_robot(const Robot &robot, int type) const;

    void draw_board(GameWorld &world) const;

    void draw_robots(const std::list<Robot> &robots, int type) const;

    void draw_factory(const RobotFactory &factory) const;

    void draw_factories(GameWorld &world) const;

    void draw_invisible_cell(GameWorld &world) const;

    sf::Vector2f get_center(int x, int y) const;

    sf::Vector2f get_coordinates_cell(int x, int y) const;
};
