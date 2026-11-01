#include <Iteraction//IAbility.h>


Ability &IAbility::get_area_damage() {
    return *ability[AbilityType::AreaDamage];
}

Ability &IAbility::get_fair_damage() {
    return *ability[AbilityType::FairDamage];
}

Ability &IAbility::get_heal_ability() {
    return *ability[AbilityType::Heal];
}

Ability &IAbility::get_teleports() {
    return *ability[AbilityType::Teleports];
}

std::map<AbilityType, std::unique_ptr<Ability> > &IAbility::get_ability() {
    return ability;
}
