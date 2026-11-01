#pragma once
#include <Graphics/DrawBase.h>
#include <Other/DisplayMode.h>

class GameWorld;

class DrawHighlight : public virtual DrawBase {
protected:
    DisplayMode display_mode = DisplayMode::Standard;

    DrawHighlight(sf::RenderWindow &window);

    virtual void change_display_mode();

    virtual void draw_highlight(GameWorld &world) const;

    virtual void draw_highlight_cell(int x, int y, sf::Color fill, sf::Color outline) const;

    virtual void draw_display_mode() const;
};
