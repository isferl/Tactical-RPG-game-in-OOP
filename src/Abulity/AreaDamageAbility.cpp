#include <Abulity/AreaDamageAbility.h>
#include <GameMap/GameWorld.h>
#include <GameProcess/Interactions.h>
#include <Robot/Robot.h>


AreaDamageAbility::AreaDamageAbility(int level) {
    xp_to_next_level = (level + 1) * XP_TO_NEXT_LEVEL_ABILITY;
    this->level = level;
    radius = 1 + level / 2;
    energy_cost = ENERGY_COST_AREA_ABILITY;
    cooldown = 1;
}

bool AreaDamageAbility::use_ability(Robot &robot, GameWorld &world, std::pair<int, int> target) {
    if (!is_ready() || !robot.get_statis_live())
        return false;
    if (!robot.try_spend_stamina(get_energy_cost()))
        return false;
    Interactions interact;
    int x_robot = robot.get_position_on_game_x();
    int y_robot = robot.get_position_on_game_y();
    for (int y = std::max(1, y_robot - radius); y <= std::min(world.get_board().get_height(), y_robot + radius); ++y) {
        for (int x = std::max(1, x_robot - radius); x <= std::min(world.get_board().get_width(), x_robot + radius); ++
             x) {
            Robot *target = world.get_board().get_square(x, y).get_robot();
            if (target != nullptr && target->get_is_friend() != robot.get_is_friend()) {
                target->get_overload().add_turns(1);
                if (interact.interactions(world.get_board().get_square(x_robot, y_robot),
                                          world.get_board().get_square(x, y), 2)) {
                    world.clear_full_cell(x, y);
                }
            }
        }
    }
    start_cooldown();
    return true;
}

void AreaDamageAbility::upgrade() {
    while (xp >= xp_to_next_level) {
        level += 1;
        if (level % 2 == 0)
            radius += 1;
        xp -= xp_to_next_level;
    }
}

int AreaDamageAbility::get_radius() const {
    return radius;
}

AbilityType AreaDamageAbility::get_name() const {
    return AbilityType::AreaDamage;
}
