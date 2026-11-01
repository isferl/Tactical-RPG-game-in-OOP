#pragma once
#include <Graphics/DrawBase.h>
#include <Other/ItemsType.h>

class GameWorld;

class DrawItems : public virtual DrawBase {
protected:
    sf::Texture item_energy_drink;
    sf::Texture item_meat;
    sf::Texture item_strength_potion;

    DrawItems(sf::RenderWindow &window);

    virtual void draw_items(GameWorld &world) const;

    virtual void draw_item(std::pair<int, int> start, ItemsType type) const;

    virtual const sf::Texture *get_texture_for_item(ItemsType type) const;
};
