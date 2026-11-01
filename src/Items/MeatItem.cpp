#include <Items/MeatItem.h>

MeatItem::MeatItem(int heal) {
    this->heal = heal;
}

int MeatItem::use_item() {
    return heal;
}

ItemsType MeatItem::get_name() const {
    return ItemsType::Meat;
}
