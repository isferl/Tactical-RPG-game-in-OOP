#include <Robot/IRank.h>
#include <iostream>


int IRank::get_xp() const {
    return xp;
}

int IRank::get_xp_to_next_rank() const {
    return xp_to_next_rank;
}

int IRank::get_rank() const {
    return rank;
}


void IRank::set_xp(int xp) {
    if (xp < 0) {
        std::cerr << "Введено неккоректное значение!" << std::endl;
        return;
    }
    this->xp = xp;
}

void IRank::set_rank(int rank) {
    this->rank = rank;
}


void IRank::set_xp_to_next_rank(int xp) {
    if (xp <= 0) {
        std::cerr << "Введено неккоректное значение!" << std::endl;
        return;
    }
    xp_to_next_rank = xp;
}
