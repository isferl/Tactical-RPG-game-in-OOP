#pragma once

class Robot;

class ISquareRobot {
protected:
    Robot *robot = nullptr;

public:
    Robot *get_robot() const;
};
