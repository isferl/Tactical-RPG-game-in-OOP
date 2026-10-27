#pragma once
class Robot;

class IStatus {
public:
    virtual bool is_finished() const = 0;

    virtual void on_turn_end(Robot &robot) = 0;

    virtual void add_turns(int turns) = 0;

    virtual bool use_effect(Robot &robot, int damage = 0) = 0;

    virtual int get_turns() = 0;

    virtual ~IStatus() = default;
};
