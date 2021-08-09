#ifndef TRAJECTORY_PLANNER_HPP
#define TRAJECTORY_PLANNER_HPP

#include <utility>

namespace mtrn4110 {

// An interface for a generic trajectory planner.
template <typename PoseType = double, typename VelocityType = double,
          typename MotionType = std::pair<PoseType, VelocityType>>
class TrajectoryPlanner {
   public:
    // Constructor to initialise required members.
    TrajectoryPlanner(MotionType nextMotion, MotionType previousMotion)
        : nextMotion_(nextMotion), previousMotion_(previousMotion) {}

    // Mark destructor as pure virtual to force abstract class.
    virtual ~TrajectoryPlanner() = 0;

    virtual auto tick() -> void = 0;

    auto getNextMotion() const noexcept -> MotionType { return nextMotion_; }
    auto getPreviousMotion() const noexcept -> MotionType { return nextMotion_; }

   private:
    MotionType nextMotion_;
    MotionType previousMotion_;
};
}  // namespace mtrn4110

#endif  // TRAJECTORY_PLANNER_HPP