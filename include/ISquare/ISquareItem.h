#pragma once
#include <Items/Items.h>
#include <memory>

class Robot;

class ISquareItem {
protected:
    std::unique_ptr<Items> item;

    void generate_item();

public:
    bool has_item() const;

    Items *get_item() const;

    std::unique_ptr<Items> take_item();

    void remove_item();

    bool try_pick_up(Robot &robot);
};
