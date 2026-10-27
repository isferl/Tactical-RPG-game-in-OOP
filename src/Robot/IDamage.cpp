#include <Robot/IDamage.h>
#include <algorithm>
#include <iostream>


void IDamage::take_damage(int damage) {
    hp = std::max(0, hp - damage);
    if (hp <= 0)
        is_alive = false;
}

void IDamage::to_heal(const int hp) {
    this->hp = std::min(max_hp, this->hp + hp);
}


int IDamage::get_hp() const {
    return hp;
}

int IDamage::get_max_hp() const {
    return max_hp;
}

int IDamage::get_damage() const {
    return damage;
}


void IDamage::set_hp(int hp) {
    if (hp < 0) {
        std::cerr << "Введено неккоректное значение!" << std::endl;
        return;
    }
    this->hp = std::min(max_hp, hp);
}

void IDamage::set_max_hp(int max_hp) {
    if (max_hp <= 0) {
        std::cerr << "Введено неккоректное значение!" << std::endl;
        return;
    }
    hp = std::min(max_hp, hp);
    this->max_hp = max_hp;
}

void IDamage::set_damage(int damage) {
    if (damage <= 0) {
        std::cerr << "Введено неккоректное значение!" << std::endl;
        return;
    }
    this->damage = damage;
}

void IDamage::set_statis_live(bool is_alive) {
    this->is_alive = is_alive;
}

bool IDamage::get_statis_live() const {
    return is_alive;
}
