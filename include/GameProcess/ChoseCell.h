#pragma once

#include <optional>
#include <utility>
#include <Other/Input.h>
#include <GameMap/GenerateBoard.h>

class ChoseCell {
private:
    std::pair<int, int> origin{0, 0};
    std::pair<int, int> selected{0, 0};
    int max_radius = 0;

public:
    void start(std::pair<int, int> player_position, int radius);

    std::optional<std::pair<int, int> > chose_to_player(Input::Action action, Board &board);

    std::pair<int, int> get_selected() const;

    int get_radius() const;
};
