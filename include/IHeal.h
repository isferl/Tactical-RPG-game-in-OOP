#pragma once

class IHeal {
protected:
    int heal;
    bool is_heal = true;

public:
    virtual int get_heal() const;

    virtual bool get_is_heal() const;

    virtual void set_is_heal(bool heal);

    virtual ~IHeal() = default;
};
