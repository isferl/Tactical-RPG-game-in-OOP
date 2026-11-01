#include <Graphics/DrawItems.h>
#include <GameMap/GameWorld.h>
#include <Other/Constants.h>

DrawItems::DrawItems(sf::RenderWindow &window)
    : DrawBase(window) {
    load_texture(item_energy_drink, "Item/item_energy_drink.png");
    load_texture(item_meat, "Item/item_meat.png");
    load_texture(item_strength_potion, "Item/item_strength_potion.png");
}

void DrawItems::draw_items(GameWorld &world) const {
    int x_map = world.get_board().get_width() + 2;
    int y_map = world.get_board().get_height() + 2;
    for (int x = 0; x < x_map; ++x) {
        for (int y = 0; y < y_map; ++y) {
            Items *item = world.get_board().get_square(x, y).get_item();
            if (item && !world.get_board().get_square(x, y).get_robot())
                draw_item({x, y}, item->get_name());
        }
    }
}

void DrawItems::draw_item(std::pair<int, int> start, ItemsType type) const {
    sf::RectangleShape square;
    square.setSize(sf::Vector2f(CEIL_SIZE, CEIL_SIZE));
    square.setPosition(get_coordinates_cell(start.first, start.second));
    square.setTexture(get_texture_for_item(type));
    window.draw(square);
}

const sf::Texture *DrawItems::get_texture_for_item(ItemsType type) const {
    switch (type) {
        case ItemsType::EnergyDrink:
            return &item_energy_drink;
        case ItemsType::Meat:
            return &item_meat;
        case ItemsType::StrengthPotion:
            return &item_strength_potion;
    }
    return &item_energy_drink;
}

