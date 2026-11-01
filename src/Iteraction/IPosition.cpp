#include <Iteraction/IPosition.h>


int IPosition::get_position_on_game_x() const {
    return position_on_game_x;
}

int IPosition::get_position_on_game_y() const {
    return position_on_game_y;
}


void IPosition::set_position_on_game_x(int position_on_game_x) {
    this->position_on_game_x = position_on_game_x;
}

void IPosition::set_position_on_game_y(int position_on_game_y) {
    this->position_on_game_y = position_on_game_y;
}

void IPosition::set_position_on_game_xy(int position_on_game_x, int position_on_game_y) {
    this->position_on_game_x = position_on_game_x;
    this->position_on_game_y = position_on_game_y;
}
