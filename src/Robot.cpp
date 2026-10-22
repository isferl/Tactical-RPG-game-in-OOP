#include "../include/Robot.h"

class RobotPlayer;

Robot::Robot(int heal, int xp_for_kill, int max_hp, int damage, int max_stamina, int type_robot, int position_on_map_x,
             int position_on_map_y, bool is_friend) {
    this->max_hp = max_hp;
    hp = max_hp;
    this->damage = damage;
    this->max_stamina = max_stamina;
    stamina = max_stamina;
    this->type_robot = type_robot;
    this->position_on_map_x = position_on_map_x;
    this->position_on_map_y = position_on_map_y;
    this->is_friend = is_friend;
    this->heal = heal;
    this->xp_for_kill = xp_for_kill;
}


