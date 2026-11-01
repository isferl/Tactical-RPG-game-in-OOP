#pragma once
#include <Graphics/DrawBase.h>

class GameWorld;

class DrawBoard : public virtual DrawBase {
protected:
    sf::Texture texture_for_cell_easy;
    sf::Texture texture_for_cell_medium;
    sf::Texture texture_for_cell_hard;
    sf::Texture texture_for_wall;
    sf::Texture texture_for_cell_invisible_for_easy;
    sf::Texture texture_for_cell_invisible_for_medium;
    sf::Texture texture_for_cell_invisible_for_hard;

    DrawBoard(sf::RenderWindow &window);

    virtual void draw_board(GameWorld &world) const;

    virtual void draw_square(const int x, const int y, const sf::Texture &texture) const;

    virtual void draw_invisible_cell(GameWorld &world) const;
};
