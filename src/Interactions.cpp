#include "../include/Interactions.h"

bool Interactions::interactions(Square &cell1, Square &cell2) {
    if (cell1.get_robot()->get_is_friend() == cell2.get_robot()->get_is_friend()) {
        if (cell2.get_robot()->get_is_heal()) {
            cell1.get_robot()->to_heal(cell2.get_robot()->get_heal());
            cell2.get_robot()->set_is_heal(false);
        }
        return false;
    }
    if (cell1.get_robot()->get_is_friend() != cell2.get_robot()->get_is_friend()) {
        cell2.get_robot()->take_damage(cell1.get_robot()->get_damage());
        return !cell2.get_robot()->get_statis_live();
    }
    return false;
}
