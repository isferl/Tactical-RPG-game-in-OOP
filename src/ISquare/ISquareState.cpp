#include <ISquare/ISquareState.h>

bool ISquareState::get_impassable() const {
    return impassable;
}

bool ISquareState::get_motionless() const {
    return motionless;
}

int ISquareState::get_cost_cell() const {
    return cost_cell;
}

CellType ISquareState::get_type() const {
    return type_cell;
}

void ISquareState::set_cost_cell(int cost) {
    cost_cell = cost;
}

void ISquareState::set_impassable(bool flag) {
    impassable = flag;
}

void ISquareState::set_motionless(bool flag) {
    motionless = flag;
}

void ISquareState::set_type_cell(CellType type_robot) {
    type_cell = type_robot;
}
