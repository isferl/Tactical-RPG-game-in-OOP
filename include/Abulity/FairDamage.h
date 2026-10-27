#pragma once
#include <Robot/IAbility.h>
#include <Other/Constants.h>

class FairDamage : public IAbility {
protected:
    int level = 1;
    int distance = 0;
    int xp = 0;
    int xp_to_next_level = 0;
    int energy_cost = ENERGY_COST_FAIR_ABILITY;

public:
    explicit FairDamage(int level);

    bool use_ability(Robot &robot, GameWorld &world, int target_x, int target_y) override;

    int get_energy_cost() const override;

    void add_xp(int xp) override;

    int get_level() override;

    void upgrade() override;

    AbilityType get_name() const override;
};
