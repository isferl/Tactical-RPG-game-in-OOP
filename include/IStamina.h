#pragma once

class IStamina {
protected:
    int stamina;
    int max_stamina;

public:
    virtual int get_stamina() const;

    virtual int get_max_stamina() const;

    virtual void set_stamina(int stamina);

    virtual void set_max_stamina(int max_stamina);

    virtual void restore_stamina(int amount);

    virtual void spend_stamina(int stamina);

    virtual bool can_spend_stamina(int cost) const;

    virtual bool try_spend_stamina(int cost);

    virtual ~IStamina() = default;
};
