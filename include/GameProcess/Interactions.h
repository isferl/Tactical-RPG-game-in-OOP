#pragma once
#include <GameMap/Square.h>

class Interactions {
public:
    bool interactions(Square &cell1, Square &cell2, float coeff_damage = 1);
};