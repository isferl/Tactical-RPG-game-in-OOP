#pragma once
#include "../include/Player.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"

class CoutInformation {
protected:
    sf::Font font{};
    sf::Text text{};

public:
    CoutInformation(const std::string &font_path);

    void cout_hp(sf::RenderWindow &window, RobotPlayer &Player);

    void cout_xp(sf::RenderWindow &window, RobotPlayer &Player);

    void cout_stamina(sf::RenderWindow &window, RobotPlayer &Player);
};
