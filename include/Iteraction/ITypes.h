#pragma once

class ITypes {
protected:
    bool is_friend;
    int type_robot;
    int xp_for_kill;

public:
    virtual bool get_is_friend() const;

    virtual int get_xp_for_kill() const;

    virtual void set_xp_for_kill(int xp);

    virtual ~ITypes() = default;
};
