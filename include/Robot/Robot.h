#pragma once
#include <Iteraction/IDamage.h>
#include <Iteraction/IHeal.h>
#include <Iteraction/IPosition.h>
#include <Iteraction/IRank.h>
#include <Iteraction/IStamina.h>
#include <Iteraction/ITypes.h>
#include <Iteraction/IAbility.h>
#include <Iteraction/IStatus.h>

class Robot : public IStamina, public IDamage, public IHeal, public IPosition, public ITypes, public IRank,
              public IAbility, public IStatus {
protected:

public:
    Robot(int heal, int xp_for_kill, int max_hp, int damage, int max_stamina, int type_robot, int position_on_map_x,
          int position_on_map_y, bool is_friend);

    virtual void multi_rank_up(int rank);

    virtual void rank_up();

    virtual void update_xp(int xp);
};
