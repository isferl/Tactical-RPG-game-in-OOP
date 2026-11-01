#pragma once
#include <map>
#include <memory>
#include <Status/Status.h>
#include <Other/StatusType.h>

class IStatus {
protected:
    std::map<StatusType, std::unique_ptr<Status> > statues;
public:
    virtual std::map<StatusType, std::unique_ptr<Status> > &get_statues();

    virtual Status &get_overload();

    virtual Status &get_shield();

    virtual Status &get_slowdown();

    virtual Status &get_burning();
};
