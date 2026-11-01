#include <Abulity/HealAbility.h>

#include <Robot/Robot.h>
#include <GameMap/GameWorld.h>
#include <cmath>

HealAbility::HealAbility(int level) {
    xp_to_next_level = (level + 1) * XP_TO_NEXT_LEVEL_ABILITY;
    this->level = level;
    heal = (level + 1) * HEAL_TO_LEVEL;
    energy_cost = ENERGY_COST_HEAL_ABILITY;
    cooldown = 2;
}

bool HealAbility::use_ability(Robot &robot, GameWorld &world, std::pair<int, int> target) {
    if (!is_ready() || !robot.get_statis_live())
        return false;
    if (!robot.try_spend_stamina(get_energy_cost()))
        return false;
    if ((heal + robot.get_hp()) > robot.get_max_hp())
        robot.get_shield().add_turns(ceil(static_cast<double>(heal + robot.get_hp() - robot.get_max_hp()) / SHIELD_BlOCK));
    robot.to_heal(heal);
    start_cooldown();
    return true;
}


void HealAbility::upgrade() {
    while (xp >= xp_to_next_level) {
        level += 1;
        heal += HEAL_TO_LEVEL;
        xp -= xp_to_next_level;
        xp_to_next_level = (level + 1) * XP_TO_NEXT_LEVEL_ABILITY;
    }
}

int HealAbility::get_radius() const {
    return 0;
}

AbilityType HealAbility::get_name() const {
    return AbilityType::Heal;
}

std::unique_ptr<Ability> HealAbility::clone() const {
    return std::make_unique<HealAbility>(*this);
}

int HealAbility::get_upgrade_value() const {
    return heal;
}
