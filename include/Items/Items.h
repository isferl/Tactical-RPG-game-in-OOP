#pragma once
#include <Other/ItemsType.h>
class Items {
protected:

public:
    virtual int use_item() = 0;

    virtual ItemsType get_name() const = 0;

    virtual ~Items() = default;


};