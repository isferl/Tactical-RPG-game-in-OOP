#pragma once
#include <Graphics/DrawBase.h>

class RobotPlayer;

class DrawInformation : public virtual DrawBase {
protected:
    DrawInformation(sf::RenderWindow &window);

    virtual void draw_player_information(RobotPlayer &player) const;
};
