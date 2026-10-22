#pragma once
#include "IStamina.h"
#include "IDamage.h"
#include "IHeal.h"
#include "IPosition.h"
#include "ITypes.h"

class Robot : public IStamina, public IDamage, public IHeal, public IPosition, public ITypes{
protected:


public:
    Robot(int heal, int xp_for_kill, int max_hp, int damage, int max_stamina, int type_robot, int position_on_map_x,
          int position_on_map_y,
          bool is_friend);


};
