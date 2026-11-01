#include <Graphics/DrawRobots.h>
#include <GameMap/GameWorld.h>
#include <Other/Constants.h>

DrawRobots::DrawRobots(sf::RenderWindow &window)
    : DrawBase(window) {
    load_texture(robot_player, "Robots/robot_player.png");
    load_texture(robot_ally, "Robots/robot_ally.png");
    load_texture(robot_enemy, "Robots/robot_enemy.png");
    load_texture(texture_for_factory, "Board/factory.png");
}

void DrawRobots::draw_player(GameWorld &world) const {
    sf::RectangleShape player;
    player.setSize(sf::Vector2f(CEIL_SIZE, CEIL_SIZE));
    player.setTexture(&robot_player);
    player.setOrigin(sf::Vector2f(CEIL_SIZE / 2.0, CEIL_SIZE / 2.0));
    player.setPosition(get_center(world.get_player().get_position_on_game_x(),
                                  world.get_player().get_position_on_game_y()));
    window.draw(player);
}

void DrawRobots::draw_robot(const Robot &robot, CellType type) const {
    if (!robot.get_statis_live()) {
        return;
    }
    sf::RectangleShape robot_draw;
    robot_draw.setSize(sf::Vector2f(CEIL_SIZE, CEIL_SIZE));
    if (type == CellType::AllyType)
        robot_draw.setTexture(&robot_ally);
    else
        robot_draw.setTexture(&robot_enemy);
    robot_draw.setOrigin(sf::Vector2f(CEIL_SIZE / 2.0, CEIL_SIZE / 2.0));
    robot_draw.setPosition(get_center(robot.get_position_on_game_x(), robot.get_position_on_game_y()));
    window.draw(robot_draw);
}

void DrawRobots::draw_factory(const RobotFactory &factory) const {
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

void DrawRobots::draw_factories(GameWorld &world) const {
    for (const auto &factory: world.get_factories())
        draw_factory(factory);
}

void DrawRobots::draw_robots(const std::list<Enemy> &robots, CellType type) const {
    for (const auto &robot: robots)
        draw_robot(robot, type);
}

void DrawRobots::draw_robots(const std::list<Ally> &robots, CellType type) const {
    for (const auto &robot: robots)
        draw_robot(robot, type);
}

