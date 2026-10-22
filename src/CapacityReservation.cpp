#include "../include/CapacityReservation.h"
#include <vector>
void CapacityReservation::spawn_entities(Board &board, FullMap &map, std::vector<Robot> &robot, int count_robots,
                                         int type_robot, bool is_friend, std::vector<std::pair<int, int> > &coordinate,
                                         int xp_for_kill) {
    for (int i = 0; i < count_robots; ++i)
        robot.emplace_back(HEAL, xp_for_kill, MAX_HP, DAMAGE, MAX_STAMINA, type_robot, coordinate[i].first, coordinate[i].second,
                           is_friend);
    for (auto &robot1: robot) {
        int ax = robot1.get_position_on_map_x();
        int ay = robot1.get_position_on_map_y();
        board.get_field()[ay][ax].set_type_cell(type_robot, map, ax, ay);
        board.get_field()[ay][ax].set_robot(&robot1);
    }
}
