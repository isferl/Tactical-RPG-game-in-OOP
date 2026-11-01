#pragma once
#include <Other/CellType.h>

class ISquareState {
protected:
    bool impassable = false;
    bool motionless = false;
    CellType type_cell = CellType::EmptyType;
    int cost_cell = 0;

public:
    bool get_impassable() const;

    bool get_motionless() const;

    int get_cost_cell() const;

    CellType get_type() const;

    void set_cost_cell(int cost);

    void set_impassable(bool flag);

    void set_motionless(bool flag);

    void set_type_cell(CellType type_robot);
};
