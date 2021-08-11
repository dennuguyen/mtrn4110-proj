#ifndef EPUCK_MOTION_PLANNER_HPP
#define EPUCK_MOTION_PLANNER_HPP

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
    EPuckMotionPlanner(double motorPosition, double motorVelocity)
    : MotionPlanner<AngleType, DistanceType, LinearVelocityType, AngularVelocityType>(motorPosition,
                                                                                      motorVelocity) {
    }

    // Compute the required motor position and velocity setpoints to achieve the given kinematics.
    auto computeMotorSetpoints(AngleType angle,
                               DistanceType distance,
                               LinearVelocityType linearVelocity,
                               AngularVelocityType angularVelocity) -> void override final {
        (void)angle;
        (void)distance;
        (void)linearVelocity;
        (void)angularVelocity;
    }

   private:
    // Write any required data to an output stream.
    auto print(std::ostream& os) const noexcept -> void override final {
        (void)os;
    }
};
}  // namespace mtrn4110

#endif  // EPUCK_MOTION_PLANNER_HPP