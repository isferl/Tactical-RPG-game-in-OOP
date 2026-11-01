#include <GameMap/GenerateGame.h>
#include <iostream>
#include <vector>
#include <utility>
#include <Other/NeedFunction.h>
#include <Other/CellType.h>
#include <Other/CostCell.h>
#include <Other/Constants.h>


void GenerateGame::set_cost_cell(Board &board, std::pair<int, int> dot, CostCell cost_cell) {
    board.get_square(dot.first, dot.second).set_cost_cell(cost_cell);
}

void GenerateGame::set_wall(Board &board, std::pair<int, int> dot) {
    board.get_square(dot.first, dot.second).set_impassable(true);
    board.set_type_in_xy(dot.first, dot.second, CellType::WallType);
}

void GenerateGame::set_factory(Board &board, std::pair<int, int> dot) {
    for (int y = 0; y < FACTORY_X; ++y)
        for (int x = 0; x < FACTORY_Y; ++x) {
            board.get_square(dot.first + x, dot.second + y).set_type_cell(CellType::FactoryType);
            board.get_square(dot.first + x, dot.second + y).set_motionless(true);
        }
}

void GenerateGame::place_robot(Robot &robot, Board &board, std::pair<int, int> dot, CellType type) {
    board.get_square(dot.first, dot.second).set_type_cell(type);
    board.get_square(dot.first, dot.second).set_robot(&robot);
}

void GenerateGame::create(GameWorld &world, LevelConfig &config) {
    std::deque<std::string> game_map = config.layout;
    int y = 0;
    while (game_map.size()) {
        std::string str = game_map.front();
        game_map.pop_front();
        for (int x = 0; x < str.size(); x++) {
            if (config.cell_types[str[x]].impassable)
                set_wall(world.get_board(), {x + 1, y + 1});
            else
                set_cost_cell(world.get_board(), {x + 1, y + 1}, config.cell_types[str[x]].cost);
        }
        ++y;
    }
    place_robot(world.get_player(), world.get_board(), {
                    world.get_player().get_position_on_game_x(), world.get_player().get_position_on_game_y()
                }, CellType::PlayerType);
    for (auto &enemy: world.get_enemies()) {
        place_robot(enemy, world.get_board(), {enemy.get_position_on_game_x(), enemy.get_position_on_game_y()},
                    CellType::EnemyType);
    }
    for (auto &ally: world.get_allies()) {
        place_robot(ally, world.get_board(), {ally.get_position_on_game_x(), ally.get_position_on_game_y()},
                    CellType::AllyType);
    }
    for (auto &factory: world.get_factories()) {
        set_factory(world.get_board(), {factory.get_position_x(), factory.get_position_y()});
    }

    for (int i = 0; i < COUNT_STATUS_FOR_TURN; ++i) {
        set_random_status_for_random_cell(world);
    }
    for (int i = 0; i < COUNT_ITEMS_FOR_TURN; ++i) {
        set_random_items_for_random_cell(world);
    }
}

void GenerateGame::set_random_status_for_random_cell(GameWorld &world) {
    Board &board = world.get_board();
    std::vector<std::pair<int, int> > cells;
    for (int y = 1; y <= board.get_height(); ++y)
        for (int x = 1; x <= board.get_width(); ++x) {
            Square &cell = board.get_square(x, y);
            if (cell.can_generate_content() && cell.get_size_statuses() < 2)
                cells.emplace_back(x, y);
        }

    if (cells.empty())
        return;

    int index = NeedFunction::get_random_number(0, static_cast<int>(cells.size()) - 1);
    std::pair<int, int> dot = cells[index];
    board.get_square(dot.first, dot.second).set_random_status();
}

void GenerateGame::set_random_items_for_random_cell(GameWorld &world) {
    Board &board = world.get_board();
    std::vector<std::pair<int, int> > cells;
    for (int y = 1; y <= board.get_height(); ++y)
        for (int x = 1; x <= board.get_width(); ++x) {
            Square &cell = board.get_square(x, y);
            if (cell.can_generate_content() && !cell.has_item())
                cells.emplace_back(x, y);
        }

    if (cells.empty())
        return;

    int index = NeedFunction::get_random_number(0, static_cast<int>(cells.size()) - 1);
    std::pair<int, int> dot = cells[index];
    board.get_square(dot.first, dot.second).set_random_item();
}
