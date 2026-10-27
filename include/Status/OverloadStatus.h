#pragma once

#include "../Robot/IStatus.h"

class OverloadStatus : public IStatus {
private:
    bool work;

public:
    explicit OverloadStatus(bool work = false);

    bool is_finished() const override;

    void on_turn_end(Robot &robot) override;

    void add_turns(int turns) override;

    bool use_effect(Robot &robot, int damage) override;

    int get_turns() override;
};
