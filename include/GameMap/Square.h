#pragma once
#include <ISquare/ISquareStatus.h>
#include <ISquare/ISquareItem.h>
#include <ISquare/ISquareState.h>
#include <ISquare/ISquareView.h>
#include <ISquare/ISquareRobot.h>

class Square : public ISquareStatus, public ISquareItem, public ISquareState, public ISquareView, public ISquareRobot {
public:
    Square(float size, bool impassable, bool motionless, int cost);

    void clear_cell();

    void set_robot(Robot *robot);

    bool can_generate_content() const;

    void set_random_status();

    void set_random_item();
};
