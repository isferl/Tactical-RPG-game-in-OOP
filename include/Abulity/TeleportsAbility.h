#pragma once
#include <Abulity/Ability.h>
#include <Other/Constants.h>
#include <Abulity/BasicMethodsAbility.h>

class TeleportsAbility : public BasicMethodsAbility {
private:
    int radius = 5;

    void upgrade() override;

public:
    std::unique_ptr<Ability> clone() const override;

    int get_upgrade_value() const override;

    explicit TeleportsAbility(int level);

    bool use_ability(Robot &robot, GameWorld &world, std::pair<int, int> target) override;

    int get_energy_cost() const override;

    int get_radius() const override;

    AbilityType get_name() const override;
};
