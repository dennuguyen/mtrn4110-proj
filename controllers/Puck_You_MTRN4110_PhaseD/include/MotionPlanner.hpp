#ifndef MOTION_PLANNER_HPP
#define MOTION_PLANNER_HPP

#include "Util.hpp"

namespace mtrn4110 {
// An interface for a generic motion planner.
template<typename PoseType = defaultType::PoseType, typename VelocityType = defaultType::VelocityType>
class MotionPlanner {
   public:
    // Initialise the motion planner with zero pose and zero velocity.
    MotionPlanner()
    : pose_({0, 0})
    , velocity(0) {}

    // Initialise the motion planner with a pose and velocity.
    MotionPlanner(PoseType pose, VelocityType velocity)
    : pose_(pose)
    , velocity_(velocity) {}

    // Automate any simple and periodic behaviours.
    virtual auto tick() -> void = 0;

    auto getNextMotion() const noexcept -> MotionType {
        return nextMotion_;
    }

    auto getPreviousMotion() const noexcept -> MotionType {
        return nextMotion_;
    }

    // Operator overload for <<.
    friend auto operator<<(std::ostream& os, MotionPlanner const& MotionPlanner) noexcept
        -> std::ostream& {
        MotionPlanner.print(os);
        return os;
    }

   private:
    // Write any required data to an output stream.
    virtual auto print(std::ostream& os) const noexcept -> void = 0;

    PoseType pose_;
    VelocityType velocity_;
};
}  // namespace mtrn4110

#endif  // MOTION_PLANNER_HPP