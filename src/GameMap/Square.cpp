#include <GameMap/Square.h>

Square::Square(float size, bool impassable, bool motionless, int cost) {
    this->size = size;
    this->impassable = impassable;
    this->motionless = motionless;
    cost_cell = cost;
}

void Square::clear_cell() {
    robot = nullptr;
    type_cell = CellType::EmptyType;
}

void Square::set_robot(Robot *robot) {
    this->robot = robot;
    if (robot != nullptr)
        set_states_to_robot(*robot);
}

bool Square::can_generate_content() const {
    if (impassable || motionless)
        return false;

    return type_cell == CellType::EmptyType || type_cell == CellType::PlayerType || type_cell == CellType::EnemyType ||
           type_cell == CellType::AllyType;
}

void Square::set_random_status() {
    if (!can_generate_content())
        return;

    ISquareStatus::set_random_status();
}

void Square::set_random_item() {
    if (has_item() || !can_generate_content())
        return;

    generate_item();
}
