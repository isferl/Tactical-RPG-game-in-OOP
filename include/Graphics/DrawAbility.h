#pragma once
#include <Graphics/DrawBase.h>

class RobotPlayer;

class DrawAbility : public virtual DrawBase {
protected:
    sf::Texture ability_area_damage;
    sf::Texture ability_fair_damage;
    sf::Texture ability_heal;
    sf::Texture ability_teleport;

    DrawAbility(sf::RenderWindow &window);

    virtual void draw_player_abilities(RobotPlayer &player) const;
};
