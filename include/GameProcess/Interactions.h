#pragma once
#include <GameMap/Square.h>

class Interactions {
public:
    bool interactions(const Square &cell1, const Square &cell2, float coeff_damage = 1);
};