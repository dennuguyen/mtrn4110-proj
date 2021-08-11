#ifndef TASK_CONTROL_HPP_
#define TASK_CONTROL_HPP_

#include <vector>

#include "Timer.hpp"

namespace mtrn4110 {
class TaskControl {
   public:
    TaskControl(int numLocks, int numTimers);
    TaskControl(TaskControl const& taskControl) = delete;
    TaskControl(TaskControl&& taskControl) noexcept = delete;
    ~TaskControl() = default;
    auto operator=(TaskControl const& taskControl) -> TaskControl& = delete;
    auto operator=(TaskControl&& taskControl) noexcept -> TaskControl& = delete;

    // Lock methods.
    auto acquireLock(int lock) -> void;
    auto releaseLock(int lock) -> void;
    auto isLockBusy(int lock) const -> bool;

    // Timer methods.
    auto time(int timer, double duration) -> void;
    auto expired(int timer) const -> bool;

   private:
    unsigned int step_ = 0;
    int numLocks_;
    int numTimers_;
    std::vector<bool> locks_ = {false};
    std::vector<Timer> timers_;
};

}  // namespace mtrn4110

#endif  // TASK_CONTROL_HPP_