#include <Graphics/DrawInventory.h>
#include <Robot/Player.h>
#include <Other/Constants.h>

DrawInventory::DrawInventory(sf::RenderWindow &window)
    : DrawBase(window), DrawItems(window) {
    load_texture(inventory_slot, "Other/inventory_slot.png");
}

void DrawInventory::draw_inventory(RobotPlayer &player) const {
    int count = player.get_size_backpack();
    if (count <= 0)
        return;

    float width = count * INVENTORY_SLOT_SIZE;
    float x = (WINDOW_WIDTH - width) / 2.f;
    float y = WINDOW_HEIGHT - INVENTORY_SLOT_SIZE - INVENTORY_BOTTOM_OFFSET;
    float offset = (INVENTORY_SLOT_SIZE - INVENTORY_ITEM_SIZE) / 2.f;
    const auto &backpack = player.get_backpack();

    for (int i = 0; i < count; ++i) {
        sf::Vector2f position{x + i * INVENTORY_SLOT_SIZE, y};
        sf::RectangleShape slot({INVENTORY_SLOT_SIZE, INVENTORY_SLOT_SIZE});
        slot.setTexture(&inventory_slot);
        slot.setPosition(position);
        window.draw(slot);

        if (i < static_cast<int>(backpack.size()) && backpack[i]) {
            sf::RectangleShape item({INVENTORY_ITEM_SIZE, INVENTORY_ITEM_SIZE});
            item.setTexture(get_texture_for_item(backpack[i]->get_name()));
            item.setPosition(position + sf::Vector2f{offset, offset});
            window.draw(item);
        }
    }
}

