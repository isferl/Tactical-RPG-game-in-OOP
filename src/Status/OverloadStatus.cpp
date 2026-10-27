#include <Status/OverloadStatus.h>


OverloadStatus::OverloadStatus(bool work) {
    this->work = work;
}

bool OverloadStatus::is_finished() const {
    return !work;
}

void OverloadStatus::on_turn_end(Robot &robot) {
}

void OverloadStatus::add_turns(int turns) {
    work = true;

}

bool OverloadStatus::use_effect(Robot&, int) {
    if (is_finished())
        return true;

    work = false;
    return false;
}

int OverloadStatus::get_turns() {
    return work;
}
