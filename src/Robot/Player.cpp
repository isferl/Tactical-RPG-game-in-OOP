#include <Robot/Player.h>
#include <Other/Constants.h>

RobotPlayer::RobotPlayer(int heal, int max_hp, int damage, int max_stamina, int type_robot,
                         int position_on_map_x,
                         int position_on_map_y) : Robot(heal, 0,  max_hp, damage, max_stamina, type_robot,
                                                        position_on_map_x,
                                                        position_on_map_y,
                                                        true) {
}

int RobotPlayer::get_visibility_distance() const {
    return visibility_distance;
}

void RobotPlayer::rank_up() {
    Robot::rank_up();
    if (get_rank() % 5 == 0)
        visibility_distance += VISIBILITY_DISTANCE_UP_FOR_RANK;
}
