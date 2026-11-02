#include <GameProcess/ChoseCell.h>
#include <Other/NeedFunction.h>

void ChoseCell::start(std::pair<int, int> player_position, int radius) {
    origin = player_position;
    selected = player_position;
    max_radius = radius;
}

std::optional<std::pair<int, int> > ChoseCell::chose_to_player(Input::Action action, Board &board) {
    if (action == Input::Action::Confirm)
        return selected;

    std::pair<int, int> next = selected;

    switch (action) {
        case Input::Action::MoveLeft:
            --next.first;
            break;
        case Input::Action::MoveRight:
            ++next.first;
            break;
        case Input::Action::MoveUp:
            --next.second;
            break;
        case Input::Action::MoveDown:
            ++next.second;
            break;
        default:
            return std::nullopt;
    }

    if (next.first < 1 || next.first > board.get_width() || next.second < 1 || next.second > board.get_height())
        return std::nullopt;

    if (NeedFunction::distance(origin.first, origin.second, next.first, next.second) <= max_radius)
        selected = next;

    return std::nullopt;
}

std::pair<int, int> ChoseCell::get_selected() const {
    return selected;
}

int ChoseCell::get_radius() const {
    return max_radius;
}
