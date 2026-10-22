#pragma once

class IPosition {
protected:
    int position_on_map_x;
    int position_on_map_y;

public:
    virtual int get_position_on_map_x() const;

    virtual int get_position_on_map_y() const;

    virtual void set_position_on_map_x(int position_on_map_x);

    virtual void set_position_on_map_y(int position_on_map_y);

    virtual void set_position_on_map_xy(int position_on_map_x, int position_on_map_y);

    virtual ~IPosition() = default;
};
