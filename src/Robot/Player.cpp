#include <Robot/Player.h>
#include <Other/Constants.h>
#include <Abulity/AreaDamageAbility.h>
#include <Abulity/FairDamageAbility.h>
#include <Other/ItemsType.h>
#include <GameMap/GameWorld.h>
#include <cstddef>


RobotPlayer::RobotPlayer(int heal, int max_hp, int damage, int max_stamina, int type_robot,
                         int position_on_map_x,
                         int position_on_map_y) : Robot(heal, 0, max_hp, damage, max_stamina, type_robot,
                                                        position_on_map_x,
                                                        position_on_map_y,
                                                        true) {
    ability.emplace(AbilityType::AreaDamage, std::make_unique<AreaDamageAbility>(0));
    ability.emplace(AbilityType::FairDamage, std::make_unique<FairDamageAbility>(0));
    point_update = 1;
    time_boost_damage = 0;
}

int RobotPlayer::get_visibility_distance() const {
    return visibility_distance;
}

void RobotPlayer::rank_up() {
    Robot::rank_up();
    ++point_update;
    if (get_rank() % 5 == 0)
        visibility_distance += VISIBILITY_DISTANCE_UP_FOR_RANK;
}

void RobotPlayer::update_ability(int xp, AbilityType type) {
    get_ability()[type]->add_xp(xp);
    --point_update;
}

int RobotPlayer::get_point_update() const {
    return point_update;
}

bool RobotPlayer::has_point_update() const {
    return point_update != 0;
}

bool RobotPlayer::pick_up_item(GameWorld &world) {
    int x = get_position_on_game_x();
    int y = get_position_on_game_y();
    return world.get_board().get_square(x, y).try_pick_up(*this);
}

bool RobotPlayer::use_item_to_index(int index) {
    if (index >= backpack.size())
        return false;
    if (backpack[index] == nullptr)
        return false;
    if (!use_item_to_player(*backpack[index]))
        return false;
    backpack.erase(backpack.begin() + index);
    return true;
}

bool RobotPlayer::use_item_to_player(Items &item) {
    int value = item.use_item();
    switch (item.get_name()) {
        case ItemsType::StrengthPotion:
            boost_damage = value;
            time_boost_damage += STRENGTH_POTION_TIME;
            return true;
        case ItemsType::EnergyDrink:
            if (get_stamina() >= get_max_stamina())
                return false;
            add_stamina(value);
            return true;
        case ItemsType::Meat:
            if (get_hp() >= get_max_hp())
                return false;
            to_heal(value);
            return true;
    }
    return false;
}

void RobotPlayer::turn_end_item() {
    if (time_boost_damage > 0)
        --time_boost_damage;
    if (time_boost_damage == 0)
        boost_damage = 0;
}

int RobotPlayer::get_damage() const {
    return Robot::get_damage() + boost_damage;
}
