#pragma once

class ISquareView {
protected:
    float size = 0;
    bool is_visibility = false;

public:
    float get_size() const;

    bool get_visibility() const;

    void set_visibility(bool visibility);
};
