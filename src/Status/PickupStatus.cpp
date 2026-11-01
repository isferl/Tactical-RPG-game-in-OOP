#include <Status/PickupStatus.h>
#include <Robot/Player.h>
#include <utility>

PickupStatus::PickupStatus(std::unique_ptr<Items> &item) : item(item) {
}

bool PickupStatus::is_finished() const {
    return item == nullptr;
}

bool PickupStatus::use_effect(Robot &robot, int) {
    if (is_finished())
        return false;
    RobotPlayer *player = dynamic_cast<RobotPlayer *>(&robot);
    if (player == nullptr || !player->get_statis_live())
        return false;
    int capacity = player->get_size_backpack();
    if (capacity <= 0 || player->get_backpack().size() >= capacity)
        return false;
    player->get_backpack().push_back(std::move(item));
    return true;
}

void PickupStatus::on_turn_end(Robot &) {
}

void PickupStatus::add_turns(int) {
}

int PickupStatus::get_turns() {
    if (is_finished())
        return 0;
    return 1;
}
