#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <utility>

class DrawBase {
protected:
    sf::RenderWindow &window;
    sf::Font card_font;

    DrawBase(sf::RenderWindow &window);

    virtual void load_texture(sf::Texture &texture, std::string path);

    virtual void draw_player_text(const std::string &str, sf::Vector2f position, unsigned int size = 16) const;

    virtual sf::Vector2f get_center(const int x, const int y) const;

    virtual sf::Vector2f get_coordinates_cell(const int x, const int y) const;

    virtual void draw_rectangle(std::pair<int, int> start, float offset_y, float height, sf::Color color) const;

public:
    virtual ~DrawBase() = default;
};
