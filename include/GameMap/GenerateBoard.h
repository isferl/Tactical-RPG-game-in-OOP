#pragma once
#include <vector>
#include <GameMap/Square.h>
#include <Other/CellType.h>

class Board {
private:
    int height;
    int width;
    std::vector<std::vector<Square> > field;

public:
    Board(int height, int width);

    std::vector<std::vector<Square> > &get_field();

    int get_height() const;

    int get_width() const;

    Square &get_square(int x, int y);

    CellType get_type_in_xy(int x, int y);

    void set_type_in_xy(int x, int y, CellType type);
};
