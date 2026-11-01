#pragma once
#include <Other/Constants.h>
#include <Items/Items.h>

class EnergyDrinkItem: public Items {
private:
    int energy;
public:
    EnergyDrinkItem(int energy = ENERGY_DRINK_RESTORE);

    int use_item();

    ItemsType get_name() const;
};