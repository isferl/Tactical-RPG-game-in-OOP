#include <ISquare/ISquareItem.h>
#include <Items/EnergyDrinkItem.h>
#include <Items/MeatItem.h>
#include <Items/StrengthPotionItem.h>
#include <Other/NeedFunction.h>
#include <Status/PickupStatus.h>
#include <utility>

bool ISquareItem::has_item() const {
    return item != nullptr;
}

Items *ISquareItem::get_item() const {
    return item.get();
}

void ISquareItem::generate_item() {
    if (has_item())
        return;

    switch (NeedFunction::get_random_number(1, 3)) {
        case 1:
            item = std::make_unique<EnergyDrinkItem>();
            break;
        case 2:
            item = std::make_unique<MeatItem>();
            break;
        case 3:
            item = std::make_unique<StrengthPotionItem>();
            break;
    }
}

std::unique_ptr<Items> ISquareItem::take_item() {
    return std::move(item);
}

void ISquareItem::remove_item() {
    item.reset();
}

bool ISquareItem::try_pick_up(Robot &robot) {
    PickupStatus status(item);
    return status.use_effect(robot);
}
