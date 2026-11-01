#include <ISquare/ISquareStatus.h>
#include <Robot/Robot.h>
#include <Other/NeedFunction.h>

std::list<StatusType> &ISquareStatus::get_statuses() {
    return states;
}

int ISquareStatus::get_size_statuses() const {
    return static_cast<int>(states.size());
}

void ISquareStatus::add_statuses(StatusType status) {
    if (get_size_statuses() < 2)
        states.push_back(status);
}

void ISquareStatus::set_states_to_robot(Robot &robot) {
    if (states.empty())
        return;

    for (auto status: states)
        robot.get_statues().at(status)->add_turns(1);

    if (NeedFunction::get_random_number(0, 1) == 1)
        states.pop_back();
    else
        states.pop_front();
}

void ISquareStatus::set_random_status() {
    StatusType result = StatusType::Burning;
    switch (NeedFunction::get_random_number(1, 4)) {
        case 1:
            result = StatusType::Burning;
            break;
        case 2:
            result = StatusType::Overload;
            break;
        case 3:
            result = StatusType::Shield;
            break;
        case 4:
            result = StatusType::Slowdown;
            break;
    }
    add_statuses(result);
}
