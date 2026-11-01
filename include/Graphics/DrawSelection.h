#pragma once
#include <Graphics/DrawBase.h>
#include <Other/AbilityType.h>

class GameWorld;

class DrawSelection : public virtual DrawBase {
protected:
    DrawSelection(sf::RenderWindow &window);

    virtual void draw_selected_cell(std::pair<int, int> point, GameWorld &world, AbilityType type) const;

    virtual void draw_blackout(int radius, GameWorld &world) const;
};
