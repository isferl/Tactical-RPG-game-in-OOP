#pragma once
#include <utility>
#include <memory>
#include <Other/AbilityType.h>

class Robot;
class GameWorld;

class Ability {
public:
    virtual std::unique_ptr<Ability> clone() const = 0;

    virtual int get_upgrade_value() const = 0;

    virtual bool use_ability(Robot &robot, GameWorld &world, std::pair<int, int> target) = 0;

    virtual int get_energy_cost() const = 0;

    virtual int get_xp() const = 0;

    virtual int get_xp_to_next_level() const = 0;

    virtual int get_cooldown() const = 0;

    virtual int get_remaining_cooldown() const = 0;

    virtual void upgrade() = 0;

    virtual void add_xp(int xp) = 0;

    virtual int get_level() = 0;

    virtual AbilityType get_name() const = 0;

    virtual int get_radius() const = 0;

    virtual bool is_ready() const = 0;

    virtual void on_turn_end() = 0;

    virtual ~Ability() = default;
};
