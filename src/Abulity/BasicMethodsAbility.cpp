#include <Abulity/BasicMethodsAbility.h>

int BasicMethodsAbility::get_xp() const {
    return xp;
}

int BasicMethodsAbility::get_xp_to_next_level() const {
    return xp_to_next_level;
}

int BasicMethodsAbility::get_cooldown() const {
    return cooldown;
}

int BasicMethodsAbility::get_remaining_cooldown() const {
    return remaining_cooldown;
}

int BasicMethodsAbility::get_energy_cost() const {
    return energy_cost;
}

void BasicMethodsAbility::add_xp(int xp) {
    this->xp += xp;
    if (this->xp >= xp_to_next_level)
        upgrade();
}

int BasicMethodsAbility::get_level() {
    return level;
}

bool BasicMethodsAbility::is_ready() const {
    return level > 0 && remaining_cooldown == 0;
}

void BasicMethodsAbility::start_cooldown() {
    remaining_cooldown = cooldown;
}

void BasicMethodsAbility::on_turn_end() {
    if (remaining_cooldown > 0)
        --remaining_cooldown;
}
