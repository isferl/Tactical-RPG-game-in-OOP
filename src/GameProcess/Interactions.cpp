#include <GameProcess/Interactions.h>

#include "GameMap/GameWorld.h"

bool Interactions::interactions(Square &cell1, Square &cell2, float coeff_damage) {
    Robot *attacker = cell1.get_robot();
    Robot *target = cell2.get_robot();
    if (attacker->get_is_friend() == target->get_is_friend()) {
        if (target->get_is_heal()) {
            attacker->to_heal(target->get_heal());
            target->set_is_heal(false);
        }
        return false;
    }
    if (attacker->get_is_friend() != target->get_is_friend()) {
        if (target->get_shield().use_effect(*target, (int)(attacker->get_damage() / coeff_damage))) {
        }
        if (!target->get_statis_live())
            attacker->update_xp(attacker->get_xp() + target->get_xp_for_kill());
        return !target->get_statis_live();
    }
    return false;
}
