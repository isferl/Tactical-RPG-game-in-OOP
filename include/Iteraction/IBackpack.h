#pragma once
#include <vector>
#include <Items/Items.h>
#include <Other/Constants.h>
#include <memory>

class IBackpack {
protected:
    std::vector<std::unique_ptr<Items>> backpack;
    int size_backpack;

public:
    IBackpack(int size = BACKPACK_CAPACITY);

    virtual std::vector<std::unique_ptr<Items>> &get_backpack();

    virtual Items& get_backpack_to_index(int index);

    virtual void add_item_to_backpack(std::unique_ptr<Items> item);

    virtual bool empty_backpack();

    virtual int get_size_backpack();

    virtual void remove_item_to_backpack(int index);
};
