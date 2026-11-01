#include <Abulity/FairDamageAbility.h>

#include <GameProcess/Interactions.h>
#include <Other/NeedFunction.h>
#include <Robot/Robot.h>
#include <GameMap/GameWorld.h>
#include <algorithm>

FairDamageAbility::FairDamageAbility(int level) {
    xp_to_next_level = (level + 1) * XP_TO_NEXT_LEVEL_ABILITY;
    this->level = level;
    radius = 3;
    energy_cost = ENERGY_COST_FAIR_ABILITY;
    cooldown = 3;
    damage_percent = 80 + std::max(0, level - 1) * 10;
}

bool FairDamageAbility::use_ability(Robot &robot, GameWorld &world, std::pair<int, int> target) {
    if (!is_ready() || !robot.get_statis_live())
        return false;

    Board &board = world.get_board();
    int target_x = target.first;
    int target_y = target.second;
    if (target_x < 1 || target_y < 1 ||
        target_x > board.get_width() || target_y > board.get_height())
        return false;

    int x = robot.get_position_on_game_x();
    int y = robot.get_position_on_game_y();
    if (NeedFunction::distance(x, y, target_x, target_y) > get_radius())
        return false;

    Robot *target_robot = board.get_square(target_x, target_y).get_robot();
    if (target_robot == nullptr || !target_robot->get_statis_live() || target_robot->get_is_friend() == robot.
        get_is_friend())
        return false;

    if (!robot.try_spend_stamina(get_energy_cost()))
        return false;

    target_robot->get_burning().add_turns(1);
    Interactions interact;
    if (interact.interactions(board.get_square(x, y), board.get_square(target_x, target_y), 100.f / damage_percent))
        world.clear_full_cell(target_x, target_y);

    start_cooldown();
    return true;
}

void FairDamageAbility::upgrade() {
    while (xp >= xp_to_next_level) {
        xp -= xp_to_next_level;
        ++level;
        damage_percent = 80 + std::max(0, level - 1) * 10;
        xp_to_next_level = (level + 1) * XP_TO_NEXT_LEVEL_ABILITY;
    }
}

int FairDamageAbility::get_radius() const {
    return radius;
}

AbilityType FairDamageAbility::get_name() const {
    return AbilityType::FairDamage;
}

std::unique_ptr<Ability> FairDamageAbility::clone() const {
    return std::make_unique<FairDamageAbility>(*this);
}

int FairDamageAbility::get_upgrade_value() const {
    return damage_percent;
}
