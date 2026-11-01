#include <Graphics/DrawBase.h>
#include <Other/Constants.h>
#include <iostream>

DrawBase::DrawBase(sf::RenderWindow &window)
    : window(window), card_font("../../material/Fond/HomeVideo-Regular.ttf") {
}

void DrawBase::load_texture(sf::Texture &texture, std::string path) {
    if (!texture.loadFromFile("../../material/" + path)) {
        std::cerr << "Не удалось загрузить изображение!" << std::endl;
        return;
    }
}

void DrawBase::draw_player_text(const std::string &str, sf::Vector2f position, unsigned int size) const {
    sf::Text text(card_font);
    text.setCharacterSize(size);
    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(1.f);
    text.setPosition(position);
    text.setString(sf::String::fromUtf8(str.begin(), str.end()));
    window.draw(text);
}

sf::Vector2f DrawBase::get_center(const int x, const int y) const {
    return {OFFSET_X + CEIL_SIZE * x + CEIL_SIZE / 2, OFFSET_Y + CEIL_SIZE * y + CEIL_SIZE / 2};
}

sf::Vector2f DrawBase::get_coordinates_cell(const int x, const int y) const {
    return {OFFSET_X + CEIL_SIZE * x, OFFSET_Y + CEIL_SIZE * y};
}

void DrawBase::draw_rectangle(std::pair<int, int> start, float offset_y, float height, sf::Color color) const {
    sf::RectangleShape square;
    square.setSize(sf::Vector2f(CEIL_SIZE, height));
    auto coord = get_coordinates_cell(start.first, start.second);
    coord.y += offset_y;
    square.setPosition(coord);
    square.setFillColor(color);
    square.setOutlineColor(sf::Color::Black);
    square.setOutlineThickness(-2.f);
    window.draw(square);
}

