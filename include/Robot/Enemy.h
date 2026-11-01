#pragma once
#include <Robot/Entities.h>

class Enemy : public Entities {
protected:

public:
    Enemy(int heal, int xp_for_kill, int max_hp, int damage, int max_stamina, int type_robot, int position_on_game_x, int position_on_game_y);

};
