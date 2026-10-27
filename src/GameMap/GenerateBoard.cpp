#include <GameMap/GenerateBoard.h>
#include <Other/Constants.h>

Board::Board(FullMap &map, int cost) {
    height = map.get_height();
    width = map.get_width();
    for (int y = 0; y < (height + 2); ++y) {
        std::vector<Square> temp;
        for (int x = 0; x < (width + 2); ++x) {
            if (map.get_map()[y][x] == -1) {
                temp.emplace_back(CEIL_SIZE, true, true, cost);
            }
            if (map.get_map()[y][x] == 0) {
                temp.emplace_back(CEIL_SIZE, false, false, cost);
            }
        }
        field.push_back(temp);
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
