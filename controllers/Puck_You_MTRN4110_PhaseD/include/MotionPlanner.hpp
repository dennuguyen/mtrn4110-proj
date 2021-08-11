#ifndef MOTION_PLANNER_HPP
#define MOTION_PLANNER_HPP

#include "Util.hpp"

namespace mtrn4110 {
// An interface for a generic motion planner.
template<typename AngleType = defaultTypes::AngleType,
         typename DistanceType = defaultTypes::DistanceType,
         typename LinearVelocityType = defaultTypes::LinearVelocityType,
         typename AngularVelocityType = defaultTypes::AngularVelocityType>
class MotionPlanner {
   public:
    // Initialise the motion planner with a motor position and motor velocity.
    MotionPlanner(double motorPosition, double motorVelocity)
    : motorPosition_(motorPosition)
    , motorVelocity_(motorVelocity) {}

    // Compute the required motor position and velocity setpoints to achieve the given kinematics.
    virtual auto computeMotorSetpoints(AngleType angle,
                                       DistanceType distance,
                                       LinearVelocityType linearVelocity,
                                       AngularVelocityType angularVelocity) -> void = 0;

    auto getMotorPosition() const noexcept -> double {
        return motorPosition_;
    }

    auto getMotorVelocity() const noexcept -> double {
        return motorVelocity_;
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

    double motorPosition_;
    double motorVelocity_;
};
}  // namespace mtrn4110

#endif  // MOTION_PLANNER_HPP