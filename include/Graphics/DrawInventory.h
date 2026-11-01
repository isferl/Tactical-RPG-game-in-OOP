#pragma once
#include <Graphics/DrawItems.h>

class RobotPlayer;

class DrawInventory : public DrawItems {
protected:
    sf::Texture inventory_slot;

    DrawInventory(sf::RenderWindow &window);

    virtual void draw_inventory(RobotPlayer &player) const;
};
