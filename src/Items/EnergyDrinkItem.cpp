#include <Items/EnergyDrinkItem.h>

EnergyDrinkItem::EnergyDrinkItem(int energy) {
    this->energy = energy;
}

int EnergyDrinkItem::use_item() {
    return energy;
}

ItemsType EnergyDrinkItem::get_name() const {
    return ItemsType::EnergyDrink;
}
