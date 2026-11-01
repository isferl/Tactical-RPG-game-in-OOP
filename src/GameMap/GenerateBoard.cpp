#include <iostream>
#include <GameMap/GenerateBoard.h>
#include <Other/Constants.h>

Board::Board(int height, int width) {
    if (height + width < 3 || height <= 0 || width <= 0) {
        std::cerr << "Выбранный размер поля слишком маленький!" << std::endl;
        return;
    }
    if (height > MAX_COUNT_CELL_HEIGH || width > MAX_COUNT_CELL_WIDTH) {
        std::cerr << "Выбранный размер поля слишком большой!" << std::endl;
        return;
    }
    this->height = height;
    this->width = width;
    for (int y = 0; y < (height + 2); ++y) {
        std::vector<Square> row;
        for (int x = 0; x < width + 2; ++x) {
            bool impassable = (y == 0 || y == (height + 1) || x == 0 || x == (width + 1));
            row.emplace_back(CEIL_SIZE, impassable, impassable, STAMINA_FOR_EASY_CELL);
            row.back().set_type_cell(impassable ? CellType::WallType : CellType::EmptyType);
        }
        field.push_back(std::move(row));
    }
}

std::vector<std::vector<Square> > &Board::get_field() {
    return field;
}


int Board::get_height() const {
    return height;
}

int Board::get_width() const {
    return width;
}

Square &Board::get_square(int x, int y){
    return field[y][x];
}

CellType Board::get_type_in_xy(int x, int y) {
    return field[y][x].get_type();
}

void Board::set_type_in_xy(int x, int y, CellType type) {
    field[y][x].set_type_cell(type);
}
