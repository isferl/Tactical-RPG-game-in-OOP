#pragma once
#include <Other/Constants.h>
#include <Items/Items.h>

class MeatItem: public Items {
private:
    int heal;
public:
    MeatItem(int heal = MEAT_HEALING);

    int use_item();

    ItemsType get_name() const;
};