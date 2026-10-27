#include <Abulity/AreaDamageAbility.h>

#include <GameMap/GameWorld.h>
#include <GameProcess/Interactions.h>
#include <Robot/Robot.h>


AreaDamageAbility::AreaDamageAbility(int level) {
    xp_to_next_level = (level + 1) * XP_TO_NEXT_LEVEL_ABILITY;
    this->level = level;
    radius = 1 + level / 2;
}

bool AreaDamageAbility::use_ability(Robot &robot, GameWorld &world, int target_x, int target_y) {
    if (robot.get_stamina() < get_energy_cost()) {
        return false;
    }
    robot.set_stamina(robot.get_stamina() - get_energy_cost());
    Interactions interact;
    int x_robot = robot.get_position_on_map_x();
    int y_robot = robot.get_position_on_map_y();
    for (int y = std::max(1, y_robot - radius); y <= std::min(world.get_board().get_height(), y_robot + radius); ++y) {
        for (int x = std::max(1, x_robot - radius); x <= std::min(world.get_board().get_width(), x_robot + radius); ++
             x) {
            Robot* target = world.get_board().get_square(x, y).get_robot();
            if (target != nullptr && target->get_is_friend() != robot.get_is_friend()) {
                if (interact.interactions(world.get_board().get_square(x_robot, y_robot),
                                         world.get_board().get_square(x, y), 2)) {
                    world.clear_full_cell(x, y);
                }
            }
        }
    }
    return true;
}

int AreaDamageAbility::get_energy_cost() const {
    return energy_cost;
}

void AreaDamageAbility::add_xp(int xp) {
    this->xp += xp;
    if (this->xp >= xp_to_next_level)
        upgrade();
}

int AreaDamageAbility::get_level() {
    return level;
}

void AreaDamageAbility::upgrade() {
    while (xp > xp_to_next_level) {
        level += 1;
        if (level % 2 == 0)
            radius += 1;
        xp_to_next_level -= xp;
    }
}

AbilityType AreaDamageAbility::get_name() const {
    return AbilityType::AreaDamage;
}
