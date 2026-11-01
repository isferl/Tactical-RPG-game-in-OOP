#include <Graphics/DrawHighlight.h>
#include <GameMap/GameWorld.h>
#include <Other/Constants.h>
#include <Other/NeedFunction.h>

DrawHighlight::DrawHighlight(sf::RenderWindow &window)
    : DrawBase(window) {
}

void DrawHighlight::change_display_mode() {
    switch (display_mode) {
        case DisplayMode::Standard:
            display_mode = DisplayMode::Enemies;
            break;
        case DisplayMode::Enemies:
            display_mode = DisplayMode::Impassable;
            break;
        case DisplayMode::Impassable:
            display_mode = DisplayMode::Statuses;
            break;
        case DisplayMode::Statuses:
            display_mode = DisplayMode::Standard;
            break;
    }
}

void DrawHighlight::draw_highlight(GameWorld &world) const {
    if (display_mode == DisplayMode::Standard)
        return;
    int x_player = world.get_player().get_position_on_game_x();
    int y_player = world.get_player().get_position_on_game_y();
    int visibility = world.get_player().get_visibility_distance();
    for (int y = 0; y < world.get_board().get_height() + 2; ++y) {
        for (int x = 0; x < world.get_board().get_width() + 2; ++x) {
            if (display_mode != DisplayMode::Impassable &&
                NeedFunction::distance(x_player, y_player, x, y) > visibility)
                continue;
            Square &cell = world.get_board().get_square(x, y);
            switch (display_mode) {
                case DisplayMode::Enemies:
                    if (cell.get_type() == CellType::EnemyType && cell.get_robot() != nullptr &&
                        cell.get_robot()->get_statis_live())
                        draw_highlight_cell(x, y, sf::Color::Transparent, sf::Color::Red);
                    break;
                case DisplayMode::Impassable:
                    if (cell.get_impassable() || cell.get_motionless())
                        draw_highlight_cell(x, y, sf::Color(120, 120, 120, 100), sf::Color::White);
                    break;
                case DisplayMode::Statuses:
                    if (cell.get_size_statuses() != 0)
                        draw_highlight_cell(x, y, sf::Color::Transparent, sf::Color(200, 80, 255));
                    break;
                case DisplayMode::Standard:
                    break;
            }
        }
    }
}

void DrawHighlight::draw_highlight_cell(int x, int y, sf::Color fill, sf::Color outline) const {
    sf::RectangleShape square({CEIL_SIZE, CEIL_SIZE});
    square.setPosition(get_coordinates_cell(x, y));
    square.setFillColor(fill);
    square.setOutlineColor(outline);
    square.setOutlineThickness(-3.f);
    window.draw(square);
}

void DrawHighlight::draw_display_mode() const {
    std::string mode;
    switch (display_mode) {
        case DisplayMode::Standard: mode = "Без подсветки"; break;
        case DisplayMode::Enemies: mode = "Враги"; break;
        case DisplayMode::Impassable: mode = "Непроходимые клетки"; break;
        case DisplayMode::Statuses: mode = "Клетки со статусами"; break;
    }
    draw_player_text("Подсветка: " + mode + " [Tab]", {PLAYER_PANEL_OFFSET, PLAYER_PANEL_OFFSET});
}

