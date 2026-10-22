#include "../include/Player.h"

#include <iostream>

#include "../include/Constants.h"

RobotPlayer::RobotPlayer(int heal, int max_hp, int damage, int max_stamina, int type_robot,
                         int position_on_map_x,
                         int position_on_map_y) : Robot(heal, 0,  max_hp, damage, max_stamina, type_robot,
                                                        position_on_map_x,
                                                        position_on_map_y,
                                                        true) {
}

int RobotPlayer::get_visibility_distance() const {
    return visibility_distance;
}

int RobotPlayer::get_xp() const {
    return xp;
}

int RobotPlayer::get_xp_to_next_rank() const {
    return xp_to_next_rank;
}

void RobotPlayer::update_xp(int xp) {
    this->xp += xp;
    while (this->xp >= xp_to_next_rank)
        rank_up();
}

void RobotPlayer::rank_up() {
    xp -= xp_to_next_rank;
    rank += 1;
    max_hp += MAX_HP_UP_FOR_RANK;
    hp += HP_UP_FOR_RANK;
    damage += DAMAGE_UP_FOR_RANK;
    stamina += STAMINA_UP_FOR_RANK;
    max_stamina += MAX_STAMINA_UP_FOR_RANK;
    xp_to_next_rank += XP_NEED_FOR_NEXT_RANK;
    visibility_distance += VISIBILITY_DISTANCE_UP_FOR_RANK;
}

void RobotPlayer::set_xp(int xp) {
    if (xp < 0) {
        std::cerr << "Введено неккоректное значение!" << std::endl;
        return;
    }
    this->xp = xp;
}

void RobotPlayer::set_xp_to_next_rank(int xp) {
    if (xp <= 0) {
        std::cerr << "Введено неккоректное значение!" << std::endl;
        return;
    }
    xp_to_next_rank = xp;
}
