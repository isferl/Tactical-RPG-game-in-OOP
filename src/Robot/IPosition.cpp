#include <Robot/IPosition.h>


int IPosition::get_position_on_map_x() const {
    return position_on_map_x;
}

int IPosition::get_position_on_map_y() const {
    return position_on_map_y;
}


void IPosition::set_position_on_map_x(int position_on_map_x) {
    this->position_on_map_x = position_on_map_x;
}

void IPosition::set_position_on_map_y(int position_on_map_y) {
    this->position_on_map_y = position_on_map_y;
}

void IPosition::set_position_on_map_xy(int position_on_map_x, int position_on_map_y) {
    this->position_on_map_x = position_on_map_x;
    this->position_on_map_y = position_on_map_y;
}
