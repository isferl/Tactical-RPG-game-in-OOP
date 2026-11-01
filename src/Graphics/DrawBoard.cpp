#include <Graphics/DrawBoard.h>
#include <GameMap/GameWorld.h>
#include <Other/Constants.h>
#include <Other/NeedFunction.h>

DrawBoard::DrawBoard(sf::RenderWindow &window)
    : DrawBase(window) {
    load_texture(texture_for_cell_easy, "Board/cell_normal.png");
    load_texture(texture_for_cell_medium, "Board/cell_medium.png");
    load_texture(texture_for_cell_hard, "Board/cell_hard.png");
    load_texture(texture_for_wall, "Board/cell_wall.png");
    load_texture(texture_for_cell_invisible_for_easy, "Board/cell_hidden_normal.png");
    load_texture(texture_for_cell_invisible_for_medium, "Board/cell_hidden_medium.png");
    load_texture(texture_for_cell_invisible_for_hard, "Board/cell_hidden_hard.png");
}

void DrawBoard::draw_board(GameWorld &world) const {
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

void DrawBoard::draw_square(const int x, const int y, const sf::Texture &texture) const {
    sf::RectangleShape square;
    square.setSize(sf::Vector2f(CEIL_SIZE, CEIL_SIZE));
    square.setPosition(get_coordinates_cell(x, y));
    square.setTexture(&texture);
    window.draw(square);
}

void DrawBoard::draw_invisible_cell(GameWorld &world) const {
    int x_map = world.get_board().get_width() + 2;
    int y_map = world.get_board().get_height() + 2;
    int x_player = world.get_player().get_position_on_game_x();
    int y_player = world.get_player().get_position_on_game_y();
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

