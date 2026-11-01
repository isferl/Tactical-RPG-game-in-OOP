#include <Robot/Ally.h>

Ally::Ally(int heal,int xp_for_kill, int max_hp, int damage, int max_stamina, int type_robot, int position_on_game_x,
           int position_on_game_y) : Entities(heal, xp_for_kill, max_hp, damage, max_stamina, type_robot,
                                              position_on_game_x,
                                              position_on_game_y,
                                              true) {
}
