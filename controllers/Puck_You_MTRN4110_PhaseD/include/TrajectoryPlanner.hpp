#ifndef TRAJECTORY_PLANNER_HPP
#define TRAJECTORY_PLANNER_HPP

#include "Util.hpp"

namespace mtrn4110 {

// An interface for a generic trajectory planner.
template <typename MotionType = defaultTypes::MotionType>
class TrajectoryPlanner {
   public:
    // Constructor to initialise required members.
    TrajectoryPlanner(MotionType initialMotion) : TrajectoryPlanner(initialMotion, initialMotion) {}
    TrajectoryPlanner(MotionType nextMotion, MotionType previousMotion)
        : nextMotion_(nextMotion), previousMotion_(previousMotion) {}

    // Enforce derived classes to implement this method.
    virtual auto tick() -> void = 0;

    auto getNextMotion() const noexcept -> MotionType { return nextMotion_; }
    auto getPreviousMotion() const noexcept -> MotionType { return nextMotion_; }

   private:
    MotionType nextMotion_;
    MotionType previousMotion_;
};
}  // namespace mtrn4110

#endif  // TRAJECTORY_PLANNER_HPP