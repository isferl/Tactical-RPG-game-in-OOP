#pragma once
#include <SFML/Graphics.hpp>
#include "GenerateBoard.h"
#include "Player.h"
#include "Ally.h"
#include "FactoryRobot.h"

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

public:
    RenderGame(sf::RenderWindow &window);

    void draw(const RobotPlayer &player_robot, const FullMap &map) const;

    void draw(const FullMap &map, int x, int y, const sf::Texture &texture) const;

    void draw(const Robot &robot, const FullMap &map, sf::Color color) const;

    void draw(const Board &board, FullMap &map) const;

    void draw(const std::vector<Robot> &robots, sf::Color color, FullMap &map) const;

    void draw(const RobotFactory &factory) const;

    void draw(const std::vector<RobotFactory> &factories) const;

    void draw_invisible_cell(Board &board, const RobotPlayer &player_robot, const FullMap &map) const;

    sf::Vector2f get_center(int x, int y) const;

    sf::Vector2f get_coordinates_cell(int x, int y) const;
};
