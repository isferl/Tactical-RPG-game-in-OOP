#include <Status/SlowdownStatus.h>

SlowdownStatus::SlowdownStatus(int turns) {
    remaining_turns = turns;
}

bool SlowdownStatus::is_finished() const {
    return remaining_turns <= 0;
}


void SlowdownStatus::on_turn_end(Robot &robot) {
    if (!is_finished())
        --remaining_turns;
}

void SlowdownStatus::add_turns(int turns) {
    remaining_turns += turns;
}

bool SlowdownStatus::use_effect(Robot &robot, int damage) {
    return is_finished();
}

int SlowdownStatus::get_turns() {
    return remaining_turns;
}
