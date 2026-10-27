#pragma once

#include "../Robot/IStatus.h"
#include "Other/Constants.h"

class BurningStatus : public IStatus {
private:
    int damage;
    int remaining_turns;

public:
    explicit BurningStatus(int turns, int damage = BURNING_DAMAGE);

    bool is_finished() const override;

    void on_turn_end(Robot &robot) override;

    void add_turns(int turns) override;

    bool use_effect(Robot &robot, int damage = 0) override;

    int get_turns() override;
};
