#pragma once
#include <Abulity/Ability.h>

class BasicMethodsAbility : public Ability {
protected:
    int level = 1;
    int xp = 0;
    int xp_to_next_level = 0;
    int energy_cost = 0;
    int cooldown = 0;
    int remaining_cooldown = 0;

    void start_cooldown();

public:
    int get_energy_cost() const override;

    void add_xp(int xp) override;

    int get_level() override;

    bool is_ready() const override;

    void on_turn_end() override;
};
