#include "../include/Square.h"


float Square::get_size() const {
    return size;
}

bool Square::get_impassable() const {
    return impassable;
}

bool Square::get_motionless() const {
    return motionless;
}


Square::Square(float size, bool impassable, bool motionless, int cost) : type_cell(0) {
    this->size = size;
    this->impassable = impassable;
    this->motionless = motionless;
    cost_cell = cost;
}

bool Square::get_visibility() const {
    return is_visibility;
}

int Square::get_cost_cell() const {
    return cost_cell;
}

void Square::set_cost_cell(int cost) {
    cost_cell = cost;
}


void Square::set_impassable(bool flag) {
    impassable = flag;
}

void Square::set_motionless(bool flag) {
    motionless = flag;
}

void Square::clear_cell() {
    robot = nullptr;
    type_cell = 0;
}


void Square::set_visibility(bool visibility) {
    is_visibility = visibility;
}

void Square::set_type_cell(int type_robot, FullMap &map, int x, int y) {
    type_cell = type_robot;
    map.set_map_in_xy(x, y, type_robot);
}

Robot *Square::get_robot() const {
    return robot;
}

void Square::set_robot(Robot *robot) {
    this->robot = robot;
}
