#pragma once
#include <map>
#include <memory>
#include <Other/AbilityType.h>
#include <Abulity/Ability.h>

class Ability;

class IAbility {
protected:
    std::map<AbilityType, std::unique_ptr<Ability> > ability;

public:
    virtual Ability &get_area_damage();

    virtual Ability &get_fair_damage();

    virtual Ability &get_heal_ability();

    virtual Ability &get_teleports();

    virtual std::map<AbilityType, std::unique_ptr<Ability> > &get_ability();
};
