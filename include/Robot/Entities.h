#pragma once
#include <Robot/Robot.h>
#include <Other/Constants.h>

class Entities : public Robot {
protected:
    AbilityType selected_ability;
    int visibility_distance = ENTITIES_VISIBILITY_DISTANCE;

public:
    Entities(int heal, int xp_for_kill, int max_hp, int damage, int max_stamina, int type_robot, int position_on_game_x,
             int position_on_game_y, bool is_friend);

    int get_visibility_distance() const;

    virtual void use_ability(Robot &robot, GameWorld &world, std::pair<int, int> target);

    virtual void rank_up();

    virtual AbilityType get_ability_type() const;
};
