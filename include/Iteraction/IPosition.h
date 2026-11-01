#pragma once

class IPosition {
protected:
    int position_on_game_x;
    int position_on_game_y;

public:
    virtual int get_position_on_game_x() const;

    virtual int get_position_on_game_y() const;

    virtual void set_position_on_game_x(int position_on_game_x);

    virtual void set_position_on_game_y(int position_on_game_y);

    virtual void set_position_on_game_xy(int position_on_game_x, int position_on_game_y);

    virtual ~IPosition() = default;
};
