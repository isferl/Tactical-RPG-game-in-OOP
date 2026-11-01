#include <Iteraction/IBackpack.h>

IBackpack::IBackpack(int size) {
    this->size_backpack = size;
}

std::vector<std::unique_ptr<Items> > &IBackpack::get_backpack() {
    return backpack;
}

Items &IBackpack::get_backpack_to_index(int index) {
    return *backpack[index];
}

void IBackpack::add_item_to_backpack(std::unique_ptr<Items> item) {
    if (backpack.size() < size_backpack)
        backpack.push_back(std::move(item));
}

bool IBackpack::empty_backpack() {
    return backpack.size() == 0;
}

int IBackpack::get_size_backpack() {
    return size_backpack;
}

void IBackpack::remove_item_to_backpack(int index) {
    if (!empty_backpack()) {
        backpack.erase(backpack.begin() + index);
    }
}
