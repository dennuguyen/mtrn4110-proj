#ifndef DEAD_RECKONING_HPP
#define DEAD_RECKONING_HPP

#include <utility>

#include "Models.hpp"
#include "TrajectoryPlanner.hpp"

namespace mtrn4110 {

template<typename MotionType = defaultTypes::MotionType,
         typename AngleType = defaultTypes::AngleType,
         typename DistanceType = defaultTypes::DistanceType,
         typename LinearVelocityType = defaultTypes::LinearVelocityType,
         typename AngularVelocityType = defaultTypes::AngularVelocityType>
class DeadReckoning final
: public TrajectoryPlanner<MotionType, AngleType, DistanceType, LinearVelocityType, AngularVelocityType> {
   public:
    DeadReckoning(MotionType initialMotion)
    : TrajectoryPlanner<MotionType, AngleType, DistanceType, LinearVelocityType, AngularVelocityType>(
        initialMotion,
        0,
        0,
        {0, 0, 0},
        {0, 0, 0}) {}

    auto computeKinematics() -> void override final {
        switch (this->motion_) {
        case 'L':
            // Set linear distance and velocity.
            this->distance_ = 0.0;
            this->linearVelocity_ = {0, 0, 0};

            // Set angle distance and velocity.
            this->angle_ = 90;
            this->angularVelocity_ = {0, 0, models::ePuck.maxSpeed};
            break;
        case 'R':
            // Set linear distance and velocity.
            this->distance_ = 0.0;
            this->linearVelocity_ = {0, 0, 0};

            // Set angle distance and velocity.
            this->angle_ = -90;
            this->angularVelocity_ = {0, 0, models::ePuck.maxSpeed};
            break;
        case 'F':
            // Set linear distance and velocity.
            this->distance_ = models::maze.distanceBetweenCells;
            this->linearVelocity_ = {models::ePuck.maxSpeed, 0, 0};

            // Set angle distance and velocity.
            this->angle_ = -90;
            this->angularVelocity_ = {0, 0, 0};
            break;
        case '\0': break;
        default: throw std::runtime_error("Invalid motion.");
        }
    }

   private:
    auto print(std::ostream& os) const noexcept -> void override final {
        (void)os;
    }
};
}  // namespace mtrn4110

#endif  // DEAD_RECKONING_HPP