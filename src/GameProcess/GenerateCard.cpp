#include <GameProcess/GenerateCard.h>
#include <Other/Constants.h>


GenerateCard::GenerateCard() {
    generate_card(CARD_IN_GAME);
}

std::vector<AbilityType> &GenerateCard::generate_card(int size) {
    card.clear();
    card.reserve(size);
    for (int cnt = 0; cnt < size; ++cnt) {
        card.emplace_back(generate_card());
    }
    return card;
}

AbilityType GenerateCard::generate_card() {
    int type = NeedFunction::get_random_number(0, 3);
    return static_cast<AbilityType>(type);
}

AbilityType GenerateCard::get_to_index(int index) {
    return card.at(index);
}
