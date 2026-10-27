#pragma once
#include <map>
#include <memory>
#include <Other/StatusType.h>
#include <Robot/IDamage.h>
#include <Robot/IHeal.h>
#include <Robot/IPosition.h>
#include <Robot/IRank.h>
#include <Robot/IStamina.h>
#include <Robot/IStatus.h>
#include <Robot/ITypes.h>
#include <Robot/IAbility.h>

class Robot : public IStamina, public IDamage, public IHeal, public IPosition, public ITypes, public IRank {
protected:
    std::map<StatusType, std::unique_ptr<IStatus> > statues;
    std::map<AbilityType, std::unique_ptr<IAbility> > ability;

public:
    Robot(int heal, int xp_for_kill, int max_hp, int damage, int max_stamina, int type_robot, int position_on_map_x,
          int position_on_map_y,
          bool is_friend);

    virtual void multi_rank_up(int rank);

    virtual void rank_up();

    virtual void update_xp(int xp);

    virtual std::map<StatusType, std::unique_ptr<IStatus> > &get_statues();

    virtual IStatus &get_overload();

    virtual IStatus &get_shield();

    virtual IStatus &get_slowdown();

    virtual IStatus &get_burning();

    virtual IAbility &get_area_damage();

    virtual IAbility &get_fair_damage();

    virtual IAbility &get_heal_ability();

    virtual IAbility &get_teleports();
};
