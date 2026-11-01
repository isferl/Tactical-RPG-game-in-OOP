#pragma once

class IDamage {
protected:
    int hp;
    int max_hp;
    int damage;
    bool is_alive = true;

public:
    virtual void take_damage(int damage);

    virtual void to_heal(int hp);

    virtual bool get_statis_live() const;

    virtual int get_hp() const;

    virtual int get_max_hp() const;

    virtual int get_damage() const;

    virtual void set_hp(int hp);

    virtual void set_max_hp(int max_hp);

    virtual void set_damage(int damage);

    virtual void set_statis_live(bool is_alive);

    virtual ~IDamage() = default;
};
