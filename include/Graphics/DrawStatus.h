#pragma once
#include <Graphics/DrawBase.h>
#include <Other/StatusType.h>

class GameWorld;
class RobotPlayer;

class DrawStatus : public virtual DrawBase {
protected:
    sf::Texture status_burning;
    sf::Texture status_overload;
    sf::Texture status_shield;
    sf::Texture status_slowdown;

    DrawStatus(sf::RenderWindow &window);

    virtual void draw_status_in_cell(GameWorld &world) const;

    virtual sf::Color get_color_for_status(StatusType type) const;

    virtual void draw_player_statuses(RobotPlayer &player) const;
};
