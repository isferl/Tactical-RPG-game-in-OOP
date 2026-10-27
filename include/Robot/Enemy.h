#pragma once
#include <Robot/Robot.h>

class Enemy : public Robot {
protected:

public:
    Enemy(int heal, int xp_for_kill, int max_hp, int damage, int max_stamina, int type_robot, int position_on_map_x, int position_on_map_y);

};
