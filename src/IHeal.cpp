#include "../include/IHeal.h"

int IHeal::get_heal() const {
    return heal;
}

bool IHeal::get_is_heal() const {
    return is_heal;
}

void IHeal::set_is_heal(bool heal) {
    is_heal = heal;
}
