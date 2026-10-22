#pragma once

#include "Player.h"

#include "FullMap.h"

class Square {
protected:
    float size;
    bool impassable;
    bool motionless = false;
    bool is_visibility = false;
    int type_cell;
    int cost_cell;
    Robot *robot = nullptr;

public:
    Square(float size, bool impassable, bool motionless, int cost);

    float get_size() const;

    bool get_impassable() const;

    bool get_motionless() const;

    bool get_visibility() const;

    int get_cost_cell() const;

    void set_cost_cell(int cost);

    void set_impassable(bool flag);

    void set_motionless(bool flag);

    void clear_cell();

    void set_visibility(bool visibility);

    void set_type_cell(int type_robot, FullMap &map, int x, int y);

    Robot *get_robot() const;

    void set_robot(Robot *robot);
};
