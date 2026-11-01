#pragma once
#include <Abulity/Ability.h>
#include <Other/Constants.h>
#include <Abulity/BasicMethodsAbility.h>

class HealAbility : public BasicMethodsAbility {
private:
    int heal = 0;

    void upgrade() override;

public:
    explicit HealAbility(int level);

    bool use_ability(Robot &robot, GameWorld &world, std::pair<int, int> target) override;

    int get_radius() const override;

    AbilityType get_name() const override;
};
