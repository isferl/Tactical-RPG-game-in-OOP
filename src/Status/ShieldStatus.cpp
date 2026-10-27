#include <Status/ShieldStatus.h>

#include "Robot/Robot.h"

ShieldStatus::ShieldStatus(int turns, int shield) {
    this->shield = shield;
    remaining_turns = turns;
}

bool ShieldStatus::is_finished() const {
    return remaining_turns <= 0;
}

void ShieldStatus::on_turn_end(Robot &robot) {
    if (!is_finished())
        --remaining_turns;
}

void ShieldStatus::add_turns(int turns) {
    remaining_turns += turns;
}


bool ShieldStatus::use_effect(Robot &robot, int damage) {
    if (remaining_turns * shield < damage) {
        robot.take_damage(damage - remaining_turns * shield);
        remaining_turns = 0;
        return true;
    }
    return false;
}

int ShieldStatus::get_turns() {
    return remaining_turns;
}
