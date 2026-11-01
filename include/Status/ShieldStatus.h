#pragma once
#include <Status/Status.h>
#include <Other/Constants.h>

class ShieldStatus : public Status {
private:
    int shield;
    int remaining_turns;

public:
    explicit ShieldStatus(int turns, int shield = SHIELD_BlOCK);

    bool is_finished() const override;

    void on_turn_end(Robot &robot) override;

    void add_turns(int turns) override;

    bool use_effect(Robot &robot, int damage = 0) override;

    int get_turns() override;

};
