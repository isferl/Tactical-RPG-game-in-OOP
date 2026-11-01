#pragma once
#include <Status/Status.h>
#include <Items/Items.h>
#include <memory>

class PickupStatus : public Status {
private:
    std::unique_ptr<Items> &item;

public:
    explicit PickupStatus(std::unique_ptr<Items> &item);

    bool is_finished() const override;

    bool use_effect(Robot &robot, int damage = 0) override;

    void on_turn_end(Robot &robot) override;

    void add_turns(int turns) override;

    int get_turns() override;
};
