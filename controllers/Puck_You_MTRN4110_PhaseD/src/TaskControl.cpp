#include "TaskControl.hpp"

#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace mtrn4110 {

TaskControl::TaskControl(int numLocks, int numTimers)
: numLocks_(numLocks)
, numTimers_(numTimers) {
}

auto TaskControl::acquireLock(int lock) -> void {
    if (lock < 0 || numLocks_ < lock) {
        throw std::runtime_error("Invalid lock number");
    }
    locks_.at(lock) = true;
}

auto TaskControl::releaseLock(int lock) -> void {
    if (lock < 0 || numLocks_ < lock) {
        throw std::runtime_error("Invalid lock number");
    }
    locks_.at(lock) = false;
}

auto TaskControl::isLockBusy(int lock) const -> bool {
    if (lock < 0 || numLocks_ < lock) {
        throw std::runtime_error("Invalid lock number");
    }
    return locks_.at(lock);
}

auto TaskControl::time(int timer, double duration) -> void {
    if (timer < 0 || numLocks_ < timer) {
        throw std::runtime_error("Invalid timer number");
    }
    timers_.at(timer).time(duration);
}

auto TaskControl::expired(int timer) const -> bool {
    if (timer < 0 || numLocks_ < timer) {
        throw std::runtime_error("Invalid timer number");
    }
    return timers_.at(timer).expired();
}

}  // namespace mtrn4110