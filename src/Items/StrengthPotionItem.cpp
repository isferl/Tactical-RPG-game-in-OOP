#include <Items/StrengthPotionItem.h>

StrengthPotionItem::StrengthPotionItem(int strength_up) {
    this->strength_up = strength_up;
}

int StrengthPotionItem::use_item() {
    return strength_up;
}

ItemsType StrengthPotionItem::get_name() const {
    return ItemsType::StrengthPotion;
}
