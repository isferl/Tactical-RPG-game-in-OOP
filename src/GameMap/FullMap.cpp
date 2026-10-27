#include <iostream>
#include <GameMap/FullMap.h>
#include <Other/Constants.h>

FullMap::FullMap(int height, int width) {
    if (height + width < 3) {
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
        std::vector<int> temp;
        temp.push_back(-1);
        bool imppassable = (y == 0 || y == (height + 1));
        for (int x = 0; x < width; ++x) {
            temp.push_back(-imppassable);
        }
        temp.push_back(-1);
        map.push_back(temp);
    }
}

int FullMap::get_height() const {
    return height;
}

int FullMap::get_width() const {
    return width;
}

std::vector<std::vector<int> > &FullMap::get_map() {
    return map;
}


int FullMap::get_map_in_xy(int x, int y) const {
    return map[y][x];
}

void FullMap::set_map_in_xy(int x, int y, int number) {
    map[y][x] = number;
}

// Print_Map::Print_Map(FullMap &map) {
//     std::cout << "================" << std::endl;
//     for (int y = 0; y < map.get_height() + 2; ++y) {
//         for (int x = 0; x < map.get_width() + 2; ++x) {
//             std::cout << map.get_map()[y][x] << " ";
//         }
//         std::cout << std::endl;
//     }
//     std::cout << "================" << std::endl;
// }
