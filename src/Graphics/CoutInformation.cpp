#include <Graphics/CoutInformation.h>
#include <string>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


CoutInformation::CoutInformation(const std::string &font_path)
    :font(font_path), text(font) {
    text.setCharacterSize(48);
    text.setFillColor(sf::Color::Green);
}

void CoutInformation::cout_hp(sf::RenderWindow &window, RobotPlayer &Player) {
    text.setPosition({0, 0});
    text.setString(std::to_string(Player.get_hp()) + "/" + std::to_string(Player.get_max_hp()));
    window.draw(text);
}

void CoutInformation::cout_xp(sf::RenderWindow &window, RobotPlayer &Player) {
    text.setPosition({0, 50});
    text.setString(std::to_string(Player.get_xp()) + "/" + std::to_string(Player.get_xp_to_next_rank()));
    window.draw(text);
}

void CoutInformation::cout_stamina(sf::RenderWindow &window, RobotPlayer &Player) {
    text.setPosition({0, 100});
    text.setString(std::to_string(Player.get_stamina()) + "/" + std::to_string(Player.get_max_stamina()));
    window.draw(text);
}
