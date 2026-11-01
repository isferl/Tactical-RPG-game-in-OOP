#include <Iteraction/IStatus.h>

std::map<StatusType, std::unique_ptr<Status> > &IStatus::get_statues() {
    return statues;
}

Status &IStatus::get_overload() {
    return *statues[StatusType::Overload];
}

Status &IStatus::get_shield() {
    return *statues[StatusType::Shield];
}

Status &IStatus::get_slowdown() {
    return *statues[StatusType::Slowdown];
}

Status &IStatus::get_burning() {
    return *statues[StatusType::Burning];
}