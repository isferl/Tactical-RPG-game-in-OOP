#pragma once
#include <Status/Status.h>

class SlowdownStatus : public Status {
private:
    int remaining_turns;

public:
    explicit SlowdownStatus(int turns);

    bool is_finished() const override;

    void on_turn_end(Robot &robot) override;

    void add_turns(int turns) override;

    bool use_effect(Robot &robot, int damage = 0) override;

    int get_turns() override;
};
