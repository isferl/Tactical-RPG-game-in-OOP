#include <Abulity/FairDamage.h>
#include <GameProcess/Interactions.h>
#include <Other/NeedFunction.h>
#include <Robot/Robot.h>
#include <GameMap/GameWorld.h>

FairDamage::FairDamage(int level) {
    xp_to_next_level = (level + 1) * XP_TO_NEXT_LEVEL_ABILITY;
    this->level = level;
    distance = 1 + level / 2;
}

bool FairDamage::use_ability(Robot &robot, GameWorld &world, int target_x, int target_y) {
    if (robot.get_stamina() < get_energy_cost()) {
        return false;
    }
    robot.set_stamina(robot.get_stamina() - get_energy_cost());
    Interactions interact;
    Robot *target = world.get_board().get_square(target_x, target_y).get_robot();
    if (target != nullptr && target->get_is_friend() != robot.get_is_friend()) {
        int distance_to_target = NeedFunction::distance(robot.get_position_on_map_x(), robot.get_position_on_map_y(),
                                                        target_x, target_y);
        if (interact.interactions(
            world.get_board().get_square(robot.get_position_on_map_x(), robot.get_position_on_map_y()),
            world.get_board().get_square(target_x, target_y), 2.0 / distance_to_target)) {
            world.clear_full_cell(target_x, target_y);
        }
    }
    return true;
}

int FairDamage::get_energy_cost() const {
    return energy_cost;
}

void FairDamage::add_xp(int xp) {
    this->xp += xp;
    if (this->xp >= xp_to_next_level)
        upgrade();
}

int FairDamage::get_level() {
    return level;
}

void FairDamage::upgrade() {
    while (xp > xp_to_next_level) {
        level += 1;
        if (level % 2 == 0)
            distance += 1;
        xp_to_next_level -= xp;
    }
}

AbilityType FairDamage::get_name() const {
    return AbilityType::FairDamage;
}
