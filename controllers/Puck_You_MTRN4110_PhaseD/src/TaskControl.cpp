#include "TaskControl.hpp"

#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace mtrn4110 {

TaskControl::TaskControl(webots::Robot &robot, int numLocks, int numTimers)
    : pathPlanner(PathPlanner())),
      mapping(Mapping(pathPlanPath)),
      motionControl(MotionControl(robot)),
      localisation(Localisation(robot),
      wallPerception(WallPerception(robot)),
      numLocks_(numLocks),
      numTimers_(numTimers) {}

TaskControl::TaskControl(TaskControl &&taskControl) noexcept
    : mapping(std::exchange(mapping, taskControl.mapping)),
      localisation(std::exchange(localisation, taskControl.localisation)),
      pathPlanner(std::exchange(pathPlanner, taskControl.pathPlanner)),
      trajectoryPlanner(std::exchange(trajectoryPlanner, taskControl.trajectoryPlanner)),
      waypointDeliberator(std::exchange(waypointDeliberator, taskControl.waypointDeliberator)),
      step_(std::exchange(step_, taskControl.step_)),
      locks_(std::exchange(locks_, taskControl.locks_)),
      timers_(std::exchange(timers_, taskControl.timers_)) {}

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

auto const TaskControl::isLockBusy(int lock) const -> bool {
    if (lock < 0 || numLocks_ < lock) {
        throw std::runtime_error("Invalid lock number");
    }
    return locks_.at(lock);
}

auto time(int timer, double duration) -> void {
    if (timer < 0 || numLocks_ < timer) {
        throw std::runtime_error("Invalid timer number");
    }
    timers_.at(timer).time(duration);
}

auto expired(int timer) const -> bool {
    if (timer < 0 || numLocks_ < timer) {
        throw std::runtime_error("Invalid timer number");
    }
    return timers_.at(timer).expired();
}

}  // namespace mtrn4110
