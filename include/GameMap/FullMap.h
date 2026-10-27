#pragma once
#include <vector>

class FullMap {
protected:
    std::vector<std::vector<int> > map;
    int height;
    int width;

public:
    FullMap(int height, int width);

    int get_height() const;

    int get_width() const;

    std::vector<std::vector<int> > &get_map();

    int get_map_in_xy(int x, int y) const;

    void set_map_in_xy(int x, int y, int number);
};
