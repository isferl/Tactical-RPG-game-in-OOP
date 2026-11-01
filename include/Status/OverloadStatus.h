#pragma once
#include <Status/Status.h>

class OverloadStatus : public Status {
private:
    bool work;
    bool penalty_spent;

public:
    explicit OverloadStatus(bool work = false, bool penalty_spent = false);

    bool is_finished() const override;

    void on_turn_end(Robot &robot) override;

    void add_turns(int turns) override;

    bool use_effect(Robot &robot, int damage) override;

    int get_turns() override;
};
