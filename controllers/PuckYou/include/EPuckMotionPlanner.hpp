#ifndef EPUCK_MOTION_PLANNER_HPP
#define EPUCK_MOTION_PLANNER_HPP

#include <cmath>
#include <utility>

#include "MotionPlanner.hpp"

namespace mtrn4110 {
template<typename AngleType = defaultTypes::AngleType,
         typename DistanceType = defaultTypes::DistanceType,
         typename LinearVelocityType = defaultTypes::LinearVelocityType,
         typename AngularVelocityType = defaultTypes::AngularVelocityType>
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
        motorPositions_ = contribution(distance, angle);
        motorVelocities_ = contribution(std::get<0>(linearVelocity), std::get<2>(angularVelocity));
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
        os << "Motor Positions: (" << motorPositions_.first << ", " << motorPositions_.second
           << ")\t";
        os << "Motor Velocities: (" << motorVelocities_.first << ", " << motorVelocities_.second
           << ")";
        os << std::endl;
    }

    // Helper function to compute a common equation for motor positions and velocities. Assumes the
    // wheel radius will never be zero.
    auto contribution(double const a, double const b) noexcept -> std::pair<double, double> {
        auto const lhs = a / models::ePuck.wheelRadius;
        auto const rhs = b * models::ePuck.axleLength / models::ePuck.wheelRadius / 2;
        return {lhs - rhs, lhs + rhs};
    }

    std::pair<double, double> motorPositions_;
    std::pair<double, double> motorVelocities_;
};
}  // namespace mtrn4110

#endif  // EPUCK_MOTION_PLANNER_HPP