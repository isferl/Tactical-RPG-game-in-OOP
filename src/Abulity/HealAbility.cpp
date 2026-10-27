#include <Abulity/HealAbility.h>
#include <Robot/Robot.h>
#include <GameMap/GameWorld.h>

HealAbility::HealAbility(int level) {
    xp_to_next_level = (level + 1) * XP_TO_NEXT_LEVEL_ABILITY;
    this->level = level;
    heal = (level + 1) * HEAL_TO_LEVEL;
}

bool HealAbility::use_ability(Robot &robot, GameWorld &world, int target_x, int target_y) {
    if (robot.get_stamina() < get_energy_cost()) {
        return false;
    }
    robot.set_stamina(robot.get_stamina() - get_energy_cost());
    robot.to_heal(heal);
    return true;
}

int HealAbility::get_energy_cost() const {
    return energy_cost;
}

void HealAbility::add_xp(int xp) {
    this->xp += xp;
    if (this->xp >= xp_to_next_level)
        upgrade();
}

int HealAbility::get_level() {
    return level;
}

void HealAbility::upgrade() {
    while (xp > xp_to_next_level) {
        level += 1;
        heal += HEAL_TO_LEVEL;
        xp_to_next_level -= xp;
    }
}

AbilityType HealAbility::get_name() const {
    return AbilityType::HealAbility;
}
