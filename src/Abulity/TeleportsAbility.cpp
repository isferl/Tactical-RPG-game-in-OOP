#include <Abulity/TeleportsAbility.h>

#include <Robot/Robot.h>
#include <GameMap/GameWorld.h>
#include <Other/NeedFunction.h>
#include <Other/Constants.h>
#include <algorithm>

TeleportsAbility::TeleportsAbility(int level) {
    xp_to_next_level = (level + 1) * XP_TO_NEXT_LEVEL_ABILITY;
    this->level = level;
    radius = TELEPORT_RADIUS;
    energy_cost = ENERGY_COST_TELEPORT_ABILITY;
    cooldown = 3;
}

bool TeleportsAbility::use_ability(Robot &robot, GameWorld &world, std::pair<int, int> target) {
    if (!is_ready() || !robot.get_statis_live())
        return false;

    Board &board = world.get_board();
    int target_x = target.first;
    int target_y = target.second;
    if (target_x < 1 || target_y < 1 || target_x > board.get_width() || target_y > board.get_height())
        return false;

    int x = robot.get_position_on_game_x();
    int y = robot.get_position_on_game_y();
    if (NeedFunction::distance(x, y, target_x, target_y) > get_radius())
        return false;

    Square &cell = board.get_square(target_x, target_y);
    if (cell.get_type() != CellType::EmptyType || cell.get_impassable())
        return false;

    if (!robot.try_spend_stamina(get_energy_cost()))
        return false;

    CellType type = board.get_type_in_xy(x, y);
    cell.set_type_cell(type);
    robot.set_position_on_game_xy(target_x, target_y);
    cell.set_robot(&robot);
    world.clear_full_cell(x, y);
    cell.try_pick_up(robot);

    start_cooldown();
    return true;
}

void TeleportsAbility::upgrade() {
    while (xp >= xp_to_next_level) {
        level += 1;
        xp -= xp_to_next_level;
        xp_to_next_level = (level + 1) * XP_TO_NEXT_LEVEL_ABILITY;
    }
}

int TeleportsAbility::get_energy_cost() const {
    return std::max(1, energy_cost - std::max(0, level - 1));
}

int TeleportsAbility::get_radius() const {
    return radius;
}

AbilityType TeleportsAbility::get_name() const {
    return AbilityType::Teleports;
}

std::unique_ptr<Ability> TeleportsAbility::clone() const {
    return std::make_unique<TeleportsAbility>(*this);
}

int TeleportsAbility::get_upgrade_value() const {
    return get_energy_cost();
}
