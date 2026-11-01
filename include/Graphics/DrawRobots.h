#pragma once
#include <Graphics/DrawBase.h>
#include <Other/CellType.h>
#include <list>

class GameWorld;
class Robot;
class RobotFactory;
class Enemy;
class Ally;

class DrawRobots : public virtual DrawBase {
protected:
    sf::Texture robot_player;
    sf::Texture robot_ally;
    sf::Texture robot_enemy;
    sf::Texture texture_for_factory;

    DrawRobots(sf::RenderWindow &window);

    virtual void draw_player(GameWorld &world) const;

    virtual void draw_robot(const Robot &robot, CellType type) const;

    virtual void draw_factory(const RobotFactory &factory) const;

    virtual void draw_factories(GameWorld &world) const;

    virtual void draw_robots(const std::list<Enemy> &robots, CellType type) const;

    virtual void draw_robots(const std::list<Ally> &robots, CellType type) const;
};
