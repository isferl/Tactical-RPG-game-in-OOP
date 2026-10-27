#pragma once

class IRank {
    int xp = 0;
    int xp_to_next_rank = 60;
    int rank = 1;

public:
    virtual int get_xp() const;

    virtual int get_xp_to_next_rank() const;

    virtual int get_rank() const;

    virtual void set_xp(int xp);
    virtual void set_rank(int rank);

    virtual void set_xp_to_next_rank(int xp);

    virtual ~IRank() = default;
};
