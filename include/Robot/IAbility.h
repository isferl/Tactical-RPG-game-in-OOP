#pragma once
#include <Other/AbilityType.h>

class Robot;
class GameWorld;

class IAbility {
public:
    virtual bool use_ability(Robot &robot, GameWorld &world, int target_x, int target_y) = 0;

    virtual int get_energy_cost() const = 0;

    virtual void upgrade() = 0;

    virtual void add_xp(int xp) = 0;

    virtual int get_level() = 0;

    virtual AbilityType get_name() const = 0;

    virtual ~IAbility() = default;
};
