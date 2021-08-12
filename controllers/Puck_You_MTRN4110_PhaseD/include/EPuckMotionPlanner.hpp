#ifndef EPUCK_MOTION_PLANNER_HPP
#define EPUCK_MOTION_PLANNER_HPP

#include <utility>

#include "MotionPlanner.hpp"

namespace mtrn4110 {
template<typename AngleType = double,
         typename DistanceType = double,
         typename LinearVelocityType = double,
         typename AngularVelocityType = double>
class EPuckMotionPlanner final
: public MotionPlanner<AngleType, DistanceType, LinearVelocityType, AngularVelocityType> {
   public:
    // Initialise the motion planner with a motor position and motor velocity.
    EPuckMotionPlanner()
    : MotionPlanner<AngleType, DistanceType, LinearVelocityType, AngularVelocityType>()
    , motorPositions_({0, 0})
    , motorVelocities_({0, 0}) {}

    // Compute the required motor position and velocity setpoints to achieve the given kinematics.
    auto computeMotorSetpoints(AngleType angle,
                               DistanceType distance,
                               LinearVelocityType linearVelocity,
                               AngularVelocityType angularVelocity) -> void override final {
        motorPositions_ = contribution(angle, distance);
        motorVelocities_ = contribution(linearVelocity, angularVelocity);
    }

    auto getMotorPositions() const noexcept -> std::pair<double, double> {
        return motorPositions_;
    }

    auto getMotorVelocities() const noexcept -> std::pair<double, double> {
        return motorVelocities_;
    }

   private:
    // Write any required data to an output stream.
    auto print(std::ostream& os) const noexcept -> void override final {
        (void)os;
    }

    // Helper function to compute a common equation for motor positions and velocities. Assumes the
    // wheel radius will never be zero.
    auto contribution(double const a, double const b) noexcept -> std::pair<double, double> {
        auto const c = static_cast<double>(models::ePuck.axleLength * b);
        return {(a - c) / models::ePuck.wheelRadius, (a + c) / models::ePuck.wheelRadius};
    }

    std::pair<double, double> motorPositions_;
    std::pair<double, double> motorVelocities_;
};
}  // namespace mtrn4110

#endif  // EPUCK_MOTION_PLANNER_HPP