#include <GameMap/GenerateGame.h>
#include <iostream>
#include <list>
#include <Other/NeedFunction.h>


void GenerateGame::set_cost_cell(Board &board, std::pair<int, int> dot, int cost_cell) {
    board.get_field()[dot.second][dot.first].set_cost_cell(cost_cell);
}

void GenerateGame::set_wall(FullMap &map, Board &board, std::pair<int, int> dot) {
    board.get_field()[dot.second][dot.first].set_impassable(true);
    map.set_map_in_xy(dot.first, dot.second, -1);
}

void GenerateGame::set_factory(FullMap &map, Board &board, std::pair<int, int> dot) {
    for (int y = 0; y < FACTORY_X; ++y)
        for (int x = 0; x < FACTORY_Y; ++x) {
            board.get_field()[dot.second + y][dot.first + x].set_type_cell(-3, map, x + dot.first, y + dot.second);
            board.get_field()[dot.second + y][dot.first + x].set_motionless(true);
        }
}

void GenerateGame::place_robot(Robot &robot, FullMap &map, Board &board, std::pair<int, int> dot, int type) {
    board.get_field()[dot.second][dot.first].set_type_cell(type, map, dot.first, dot.second);
    board.get_field()[dot.second][dot.first].set_robot(&robot);
}

void GenerateGame::create(GameWorld &world, LevelConfig &config) {
    std::deque<std::string> game_map = config.layout;
    int y = 0;
    while (game_map.size()) {
        std::string str = game_map.front();
        game_map.pop_front();
        for (int x = 0; x < str.size(); x++) {
            if (config.cell_types[str[x]].impassable)
                set_wall(world.get_map(), world.get_board(), {x + 1, y + 1});
            else
                set_cost_cell(world.get_board(), {x + 1, y + 1}, config.cell_types[str[x]].move_cost);
        }
        ++y;
    }
    place_robot(world.get_player(), world.get_map(), world.get_board(), {
                    world.get_player().get_position_on_map_x(), world.get_player().get_position_on_map_y()
                }, 1);
    for (auto &enemy: world.get_enemies()) {
        place_robot(enemy, world.get_map(), world.get_board(), {
                        enemy.get_position_on_map_x(), enemy.get_position_on_map_y()
                    }, -2);
    }
    for (auto &ally: world.get_allies()) {
        place_robot(ally, world.get_map(), world.get_board(), {
                        ally.get_position_on_map_x(), ally.get_position_on_map_y()
                    }, 2);
    }
    for (auto &factory: world.get_factories()) {
        set_factory(world.get_map(), world.get_board(), {factory.get_position_x(), factory.get_position_y()});
    }

    for (int i = 0; i < COUNT_STATUS_FOR_TURN ; ++i) {
        set_random_status_for_random_cell(world);
    }
}

void GenerateGame::set_random_status_for_random_cell(GameWorld &world) {
    int x = NeedFunction::get_random_number(1, world.get_board().get_width());
    int y = NeedFunction::get_random_number(1, world.get_board().get_height());
    world.get_board().get_field()[y][x].set_random_status();
}
