#pragma once
#include <vector>
#include <Other/AbilityType.h>
#include <Other/NeedFunction.h>

class GenerateCard {
protected:
    std::vector<AbilityType> card;

public:
    GenerateCard();

    std::vector<AbilityType> &generate_card(int size);

    AbilityType generate_card();

    AbilityType get_to_index(int index);

    int get_size() const;
};
