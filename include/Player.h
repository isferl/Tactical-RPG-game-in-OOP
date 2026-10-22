#pragma once
#include "Robot.h"
#include "Constants.h"

class RobotPlayer : public Robot {
protected:
    int xp = 0;
    int xp_to_next_rank = 30;
    int rank = 1;
    int visibility_distance = VISIBILITY_DISTANCE;

public:
    RobotPlayer(int heal, int max_hp, int damage, int max_stamina, int type_robot, int position_on_map_x,
                int position_on_map_y);

    int get_visibility_distance() const;

    int get_xp() const;

    int get_xp_to_next_rank() const;

    void update_xp(int xp);

    void rank_up();

    void set_xp(int xp);

    void set_xp_to_next_rank(int xp);
};
