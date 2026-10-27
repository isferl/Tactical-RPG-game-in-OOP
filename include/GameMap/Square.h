#pragma once

#include <list>
#include <Robot/Player.h>
#include <Other/StatusType.h>
#include <GameMap/FullMap.h>

class Square {
protected:
    float size;
    bool impassable;
    bool motionless = false;
    bool is_visibility = false;
    int type_cell;
    int cost_cell;
    Robot *robot = nullptr;
    std::list<StatusType> states;

public:
    Square(float size, bool impassable, bool motionless, int cost);

    float get_size() const;

    bool get_impassable() const;

    bool get_motionless() const;

    bool get_visibility() const;

    int get_cost_cell() const;

    std::list<StatusType> &get_statuses();

    int get_size_statuses() const;

    void add_statuses(StatusType status);

    void set_cost_cell(int cost);

    void set_impassable(bool flag);

    void set_motionless(bool flag);

    void clear_cell();

    void set_visibility(bool visibility);

    void set_type_cell(int type_robot, FullMap &map, int x, int y);

    Robot *get_robot() const;

    void set_robot(Robot *robot);

    void set_states_to_robot(Robot &robot);

    void set_random_status();
};
