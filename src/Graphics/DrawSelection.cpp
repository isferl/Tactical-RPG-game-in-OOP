#include <Graphics/DrawSelection.h>
#include <GameMap/GameWorld.h>
#include <Other/Constants.h>
#include <Other/NeedFunction.h>

DrawSelection::DrawSelection(sf::RenderWindow &window)
    : DrawBase(window) {
}

void DrawSelection::draw_selected_cell(std::pair<int, int> point, GameWorld &world, AbilityType type) const {
    sf::RectangleShape cursor;
    cursor.setSize(sf::Vector2f(CEIL_SIZE, CEIL_SIZE));
    cursor.setPosition(get_coordinates_cell(point.first, point.second));
    Square &selected_cell = world.get_board().get_square(point.first, point.second);
    if (((selected_cell.get_type() == CellType::EnemyType) && (type == AbilityType::FairDamage)) || (
            (selected_cell.get_type() == CellType::EmptyType) && (type == AbilityType::Teleports))) {
        cursor.setFillColor(sf::Color(0, 255, 0, 50));
        cursor.setOutlineColor(sf::Color::Green);
        cursor.setOutlineThickness(-2.f);
    } else {
        cursor.setFillColor(sf::Color(255, 0, 0, 50));
        cursor.setOutlineColor(sf::Color::Red);
        cursor.setOutlineThickness(-2.f);
    }

    window.draw(cursor);
}

void DrawSelection::draw_blackout(int radius, GameWorld &world) const {
    sf::RectangleShape blackout_cell;
    blackout_cell.setSize(sf::Vector2f(CEIL_SIZE, CEIL_SIZE));
    blackout_cell.setFillColor(sf::Color(0, 0, 0, 120));
    blackout_cell.setOutlineColor(sf::Color::Black);
    blackout_cell.setOutlineThickness(-2.f);

    int x_player = world.get_player().get_position_on_game_x();
    int y_player = world.get_player().get_position_on_game_y();
    int x_map = world.get_board().get_width() + 2;
    int y_map = world.get_board().get_height() + 2;

    for (int y = 0; y < y_map; ++y) {
        for (int x = 0; x < x_map; ++x) {
            if (NeedFunction::distance(x_player, y_player, x, y) > radius) {
                blackout_cell.setPosition(get_coordinates_cell(x, y));
                window.draw(blackout_cell);
            }
        }
    }
}

