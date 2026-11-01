#pragma once
#include <Robot/Robot.h>
#include <Other/Constants.h>
#include <Iteraction/IBackpack.h>
#include <Items/Items.h>
#include <Other/ItemsType.h>

class RobotPlayer : public Robot, public IBackpack{
private:
    int point_update;
    int time_boost_damage = 0;
    int boost_damage = 0;

protected:
    int visibility_distance = VISIBILITY_DISTANCE;

public:
    RobotPlayer(int heal, int max_hp, int damage, int max_stamina, int type_robot, int position_on_map_x,
                int position_on_map_y);

    int get_visibility_distance() const;

    void rank_up() override;

    void update_ability(int xp, AbilityType type);

    int get_point_update() const;

    bool has_point_update() const;

    bool pick_up_item(GameWorld &world);

    bool use_item_to_index(int index);

    bool use_item_to_player(Items &item);

    void turn_end_item();

    int get_damage() const override;
};
