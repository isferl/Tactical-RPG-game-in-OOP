#pragma once
#include <Robot/Robot.h>
#include <Other/Constants.h>

class RobotPlayer : public Robot {
protected:
    int visibility_distance = VISIBILITY_DISTANCE;

public:
    RobotPlayer(int heal, int max_hp, int damage, int max_stamina, int type_robot, int position_on_map_x,
                int position_on_map_y);

    int get_visibility_distance() const;

    void rank_up();

};
