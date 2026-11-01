#pragma once
#include <list>
#include <Other/StatusType.h>

class Robot;

class ISquareStatus {
protected:
    std::list<StatusType> states;

public:
    std::list<StatusType> &get_statuses();

    int get_size_statuses() const;

    void add_statuses(StatusType status);

    void set_states_to_robot(Robot &robot);

    void set_random_status();
};
