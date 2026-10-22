#pragma once
#include "Square.h"
#include "FullMap.h"

class Board {
protected:
    int height;
    int width;
    std::vector<std::vector<Square> > field;

public:
    Board(FullMap &map, int cost);

    std::vector<std::vector<Square> > &get_field();

    int get_height() const;

    int get_width() const;

    const Square &get_square(int x, int y) const;
};
