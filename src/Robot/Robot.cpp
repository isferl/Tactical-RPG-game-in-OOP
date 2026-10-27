#include <algorithm>
#include <Other/Constants.h>
#include <Robot/Robot.h>
#include <Status/BurningStatus.h>
#include <Status/OverloadStatus.h>
#include <Status/ShieldStatus.h>
#include <Status/SlowdownStatus.h>
#include <Abulity/AreaDamageAbility.h>

class RobotPlayer;

Robot::Robot(int heal, int xp_for_kill, int max_hp, int damage, int max_stamina, int type_robot, int position_on_map_x,
             int position_on_map_y, bool is_friend) {
    this->max_hp = max_hp;
    hp = max_hp;
    this->damage = damage;
    this->max_stamina = max_stamina;
    stamina = max_stamina;
    this->type_robot = type_robot;
    this->position_on_map_x = position_on_map_x;
    this->position_on_map_y = position_on_map_y;
    this->is_friend = is_friend;
    this->heal = heal;
    this->xp_for_kill = xp_for_kill;
    statues.emplace(StatusType::Burning, std::make_unique<BurningStatus>(0, BURNING_DAMAGE));
    statues.emplace(StatusType::Overload, std::make_unique<OverloadStatus>(false));
    statues.emplace(StatusType::Shield, std::make_unique<ShieldStatus>(0, SHIELD_BlOCK));
    statues.emplace(StatusType::Slowdown, std::make_unique<SlowdownStatus>(0));
    ability.emplace(AbilityType::AreaDamage, std::make_unique<AreaDamageAbility>(0));
}

void Robot::multi_rank_up(int rank) {
    for (int cnt = 0; cnt < rank; ++cnt) {
        rank_up();
    }
}


void Robot::rank_up() {
    set_rank(get_rank() + 1);
    max_hp += MAX_HP_UP_FOR_RANK;
    hp += HP_UP_FOR_RANK;
    damage += DAMAGE_UP_FOR_RANK;
    stamina += STAMINA_UP_FOR_RANK;
    max_stamina += MAX_STAMINA_UP_FOR_RANK;
    set_xp_to_next_rank(get_xp_to_next_rank() + XP_NEED_FOR_NEXT_RANK);
}

void Robot::update_xp(int xp) {
    set_xp(get_xp() + xp);
    while (get_xp() >= get_xp_to_next_rank()) {
        set_xp(get_xp() - get_xp_to_next_rank());
        rank_up();
    }
}

std::map<StatusType, std::unique_ptr<IStatus> > &Robot::get_statues() {
    return statues;
}

IStatus &Robot::get_overload() {
    return *statues[StatusType::Overload];
}

IStatus &Robot::get_shield() {
    return *statues[StatusType::Shield];
}

IStatus &Robot::get_slowdown() {
    return *statues[StatusType::Slowdown];
}

IStatus &Robot::get_burning() {
    return *statues[StatusType::Burning];
}

IAbility &Robot::get_area_damage() {
    return *ability[AbilityType::AreaDamage];
}

IAbility &Robot::get_fair_damage() {
    return *ability[AbilityType::FairDamage];
}

IAbility &Robot::get_heal_ability() {
    return *ability[AbilityType::Heal];
}

IAbility &Robot::get_teleports() {
    return *ability[AbilityType::Teleports];
}
