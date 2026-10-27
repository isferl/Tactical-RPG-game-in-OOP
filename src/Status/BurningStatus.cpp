#include <Status/BurningStatus.h>

#include <Robot/Robot.h>

BurningStatus::BurningStatus(int turns, int damage) {
    remaining_turns = turns;
    this->damage = damage;
}

bool BurningStatus::is_finished() const {
    return remaining_turns <= 0;
}

void BurningStatus::on_turn_end(Robot &robot) {
    if (!is_finished()) {
        robot.get_shield().use_effect(robot, damage * remaining_turns);
        --remaining_turns;
    }

}

void BurningStatus::add_turns(int turns) {
    remaining_turns += turns;
}

bool BurningStatus::use_effect(Robot &robot, int damage) {
    return true;
}

int BurningStatus::get_turns() {
    return remaining_turns;
}




