#include <Robot/Entities.h>
#include <Other/NeedFunction.h>
#include <Other/Constants.h>

Entities::Entities(int heal, int xp_for_kill, int max_hp, int damage, int max_stamina, int type_robot,
                   int position_on_game_x, int position_on_game_y, bool is_friend) : Robot(
    heal, xp_for_kill, max_hp, damage, max_stamina, type_robot, position_on_game_x,
    position_on_game_y, is_friend) {
    int chose = NeedFunction::get_random_number(1, 2);
    switch (chose) {
        case 1:
            selected_ability = AbilityType::Teleports;
            ability[selected_ability]->add_xp(XP_FOR_RANK_UP);
            break;
        case 2:
            selected_ability = AbilityType::Heal;
            ability[selected_ability]->add_xp(XP_FOR_RANK_UP);
            break;
    }
}

int Entities::get_visibility_distance() const {
    return visibility_distance;
}

void Entities::use_ability(Robot &robot, GameWorld &world, std::pair<int, int> target) {
    ability[selected_ability]->use_ability(robot, world, target);
}

void Entities::rank_up() {
    Robot::rank_up();
    ability[selected_ability]->add_xp(XP_FOR_RANK_UP);
}

AbilityType Entities::get_ability_type() const {
    return selected_ability;
}
