#pragma once
#include <Abulity/Ability.h>
#include <Other/Constants.h>
#include <Abulity/BasicMethodsAbility.h>

class FairDamageAbility : public BasicMethodsAbility {
private:
    int radius = 0;
    int damage_percent = 80;

    void upgrade() override;

public:
    std::unique_ptr<Ability> clone() const override;

    int get_upgrade_value() const override;

    explicit FairDamageAbility(int level);

    bool use_ability(Robot &robot, GameWorld &world, std::pair<int, int> target) override;

    int get_radius() const override;

    AbilityType get_name() const override;
};
