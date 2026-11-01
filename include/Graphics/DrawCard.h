#pragma once
#include <Graphics/DrawAbility.h>

class Ability;
class GenerateCard;

class DrawCard : public DrawAbility {
protected:
    sf::Texture card_background;
    sf::Texture new_badge;
    sf::Texture level_up_badge;

    DrawCard(sf::RenderWindow &window);

    virtual void draw_cards(RobotPlayer &player, GenerateCard &cards) const;

    virtual void draw_card(Ability &ability, sf::Vector2f position, int number) const;

    virtual void draw_card_text(const std::string &str, sf::Vector2f position, unsigned int size,
                                float max_width = 0.f) const;

    virtual std::string get_card_change(int current, int next) const;
};
