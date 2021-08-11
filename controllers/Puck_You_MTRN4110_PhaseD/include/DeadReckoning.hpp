#ifndef DEAD_RECKONING_HPP
#define DEAD_RECKONING_HPP

#include <utility>

#include "Models.hpp"
#include "TrajectoryPlanner.hpp"

namespace mtrn4110 {

template<typename AngleType = defaultType::AngleType,
         typename DistanceType = defaultType::DistanceType,
         typename LinearVelocityType = defaultType::LinearVelocityType,
         typename AngularVelocityType = defaultType::AngularVelocityType,
         typename MotionType = defaultType::MotionType>
class DeadReckoning final : public TrajectoryPlanner<DistanceType, VelocityType, MotionType> {
   public:
    DeadReckoning(MotionType initialMotion)
    : TrajectoryPlanner(initialMotion, 0, {0}, {0}) {}

    auto computeKinematics() -> void override final {
        switch (motion_) {
        case 'L':
            // Set linear distance and velocity.
            distance_ = 0.0;
            linearVelocity_ = {0, 0, 0};

            // Set angle distance and velocity.
            angle_ = 90;
            angularVelocity_ = {0, 0, models::ePuck.maxSpeed};
            break;
        case 'R':
            // Set linear distance and velocity.
            distance_ = 0.0;
            linearVelocity_ = {0, 0, 0};

            // Set angle distance and velocity.
            angle_ = -90;
            angularVelocity_ = {0, 0, models::ePuck.maxSpeed};
            break;
        case 'F':
            // Set linear distance and velocity.
            distance_ = models::maze.distanceBetweenCells;
            linearVelocity_ = {models::ePuck.maxSpeed, 0, 0};

            // Set angle distance and velocity.
            angle_ = -90;
            angularVelocity_ = {0, 0, 0};
            break;
        default: throw std::runtime_error("Invalid motion.");
        }
    }

   private:
    auto print(std::ostream& os) const noexcept -> void override final {}
};  // namespace mtrn4110
}  // namespace mtrn4110

#endif  // DEAD_RECKONING_HPP