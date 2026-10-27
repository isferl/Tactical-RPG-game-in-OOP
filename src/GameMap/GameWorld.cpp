#include <GameMap/GameWorld.h>
#include <Other/Constants.h>

GameWorld::GameWorld(LevelConfig &config) : map(FullMap(config.height, config.width)),
                                            board(map, STAMINA_FOR_EASY_CELL),
                                            player(config.robots_templates["player"].heal,
                                                   config.robots_templates["player"].max_hp,
                                                   config.robots_templates["player"].damage,
                                                   config.robots_templates["player"].max_stamina,
                                                   1,
                                                   config.robots.cbegin()->position.first,
                                                   config.robots.cbegin()->position.second
                                            ) {
    auto iterations = std::next(config.robots.cbegin());
    while (iterations != config.robots.cend()) {
        if (iterations->templates == "enemy")
            enemies.emplace_back(config.robots_templates["enemy"].heal,
                                 config.robots_templates["enemy"].xp_for_kill,
                                 config.robots_templates["enemy"].max_hp,
                                 config.robots_templates["enemy"].damage,
                                 config.robots_templates["enemy"].max_stamina,
                                 -2,
                                 iterations->position.first,
                                 iterations->position.second,
                                 false);
        else if (iterations->templates == "ally")
            allies.emplace_back(config.robots_templates["ally"].heal,
                                config.robots_templates["ally"].xp_for_kill,
                                config.robots_templates["ally"].max_hp,
                                config.robots_templates["ally"].damage,
                                config.robots_templates["ally"].max_stamina,
                                2,
                                iterations->position.first,
                                iterations->position.second,
                                true);
        ++iterations;
    }
    auto iteration = config.factories.cbegin();
    while (iteration != config.factories.cend()) {
        this->factories.emplace_back(iteration->position.first,
                                     iteration->position.second,
                                     iteration->spawn_interval_turns,
                                     iteration->spawn_limit);
        ++iteration;
    }
}

FullMap &GameWorld::get_map() {
    return map;
}

Board &GameWorld::get_board() {
    return board;
}

RobotPlayer &GameWorld::get_player() {
    return player;
}

std::list<Robot> &GameWorld::get_allies() {
    return allies;
}

std::list<Robot> &GameWorld::get_enemies() {
    return enemies;
}

std::list<RobotFactory> &GameWorld::get_factories() {
    return factories;
}

void GameWorld::clear_full_cell(int x, int y) {
    board.get_square(x, y).clear_cell();
    map.set_map_in_xy(x, y, 0);
}
