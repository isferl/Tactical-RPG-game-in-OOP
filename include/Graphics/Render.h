#pragma once
#include <list>
#include <Robot/FactoryRobot.h>
#include <SFML/Graphics.hpp>
#include <Other/CellType.h>
#include <GameMap/GameWorld.h>

class RenderGame {
private:
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

    void draw_robot(const Robot &robot, CellType type) const;

    void draw_board(GameWorld &world) const;

    template<typename Type>
    void draw_robots(const std::list<Type> &robots, CellType type) const {
        for (const auto &robot: robots)
            draw_robot(robot, type);
    }

    void draw_factory(const RobotFactory &factory) const;

    void draw_factories(GameWorld &world) const;

    void draw_invisible_cell(GameWorld &world) const;

    sf::Vector2f get_center(int x, int y) const;

    sf::Vector2f get_coordinates_cell(int x, int y) const;

    void draw_selected_cell(std::pair<int, int> point, GameWorld &world, AbilityType type) const;

    void draw_blackout(int radius, GameWorld &world) const;
};
