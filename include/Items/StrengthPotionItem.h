#pragma once
#include <Other/Constants.h>
#include <Items/Items.h>

class StrengthPotionItem: public Items {
private:
    int strength_up;
public:
    StrengthPotionItem(int strength_up = STRENGTH_POTION);

    int use_item();

    ItemsType get_name() const;
};
