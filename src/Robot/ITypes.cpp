#include <Robot/ITypes.h>

bool ITypes::get_is_friend() const {
    return is_friend;
}

int ITypes::get_xp_for_kill() const {
    return xp_for_kill;
}

void ITypes::set_xp_for_kill(int xp) {
    this->xp_for_kill = xp;
}
