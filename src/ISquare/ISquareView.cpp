#include <ISquare/ISquareView.h>

float ISquareView::get_size() const {
    return size;
}

bool ISquareView::get_visibility() const {
    return is_visibility;
}

void ISquareView::set_visibility(bool visibility) {
    is_visibility = visibility;
}
