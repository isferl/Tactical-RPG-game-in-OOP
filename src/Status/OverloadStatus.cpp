#include <Status/OverloadStatus.h>
#include <Robot/Robot.h>


OverloadStatus::OverloadStatus(bool work, bool penalty_spent) {
    this->work = work;
    this->penalty_spent = penalty_spent;
}

bool OverloadStatus::is_finished() const {
    return !work && !penalty_spent;
}

void OverloadStatus::on_turn_end(Robot &robot) {
    if (penalty_spent)
        work = false;
    penalty_spent = false;
}

void OverloadStatus::add_turns(int turns) {
    work = true;
}

bool OverloadStatus::use_effect(Robot &robot, int damage) {
    if (is_finished())
        return true;
    if (!penalty_spent) {
        if (!robot.try_spend_stamina(damage))
            robot.set_stamina(0);
        penalty_spent = true;
    }
    return false;
}

int OverloadStatus::get_turns() {
    return work;
}
