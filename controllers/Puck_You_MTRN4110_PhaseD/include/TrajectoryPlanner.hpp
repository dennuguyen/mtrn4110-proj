#ifndef TRAJECTORY_PLANNER_HPP
#define TRAJECTORY_PLANNER_HPP

#include "Util.hpp"

namespace mtrn4110 {
// An interface for a generic trajectory planner.
template<typename MotionType = defaultType::MotionType>
class TrajectoryPlanner {
   public:
    // Initialise the trajectory planner with just the initial motion.
    TrajectoryPlanner(MotionType initialMotion)
    : TrajectoryPlanner(initialMotion, initialMotion) {}

    // Initialise the trajectory planner with the next and previous motions.
    TrajectoryPlanner(MotionType nextMotion, MotionType previousMotion)
    : nextMotion_(nextMotion)
    , previousMotion_(previousMotion) {}

    // Automate any simple and periodic behaviours.
    virtual auto tick() -> void = 0;

    auto getNextMotion() const noexcept -> MotionType {
        return nextMotion_;
    }
    auto getPreviousMotion() const noexcept -> MotionType {
        return nextMotion_;
    }

    // Operator overload for <<.
    friend operator<<(std::ostream& os, PathPlanner const& pathPlanner) noexcept->std::ostream& {
        pathPlanner.print(os);
        return os;
    }

   private:
    // Write any required data to an output stream.
    virtual auto print(std::ostream& os) const noexcept -> void = 0;

    MotionType nextMotion_;
    MotionType previousMotion_;
};
} // namespace mtrn4110

#endif // TRAJECTORY_PLANNER_HPP