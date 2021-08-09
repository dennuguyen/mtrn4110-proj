#ifndef TASK_CONTROL_HPP_
#define TASK_CONTROL_HPP_

#include <WaypointDeliberator.hpp>
#include <vector>
#include <webots/Robot.hpp>

#include "Localisation.hpp"
#include "Mapping.hpp"
#include "PathPlanner.hpp"
#include "TrajectoryPlanner.hpp"

namespace mtrn4110 {
class TaskControl {
   public:
    explicit TaskControl(webots::Robot&);
    TaskControl(TaskControl const&) = delete;
    TaskControl(TaskControl&&) noexcept;
    ~TaskControl() = default;
    auto operator=(TaskControl const&) -> TaskControl& = delete;
    auto operator=(TaskControl&&) -> TaskControl& = delete;
    auto tick() noexcept -> void;
    auto acquireLock() noexcept -> void;
    auto releaseLock() noexcept -> void;
    auto isLockBusy() const noexcept -> bool;

   public:
    Mapping<>& mapping;
    Localisation<>& localisation;
    PathPlanner<>& pathPlanner;
    TrajectoryPlanner<>& trajectoryPlanner;
    WaypointDeliberator<>& waypointDeliberator;

   private:
    unsigned int step_ = 0;
    bool bigLock_ = false;
};

}  // namespace mtrn4110

#endif  // TASK_CONTROL_HPP_