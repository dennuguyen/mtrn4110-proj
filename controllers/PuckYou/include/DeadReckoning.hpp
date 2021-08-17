#ifndef DEAD_RECKONING_HPP
#define DEAD_RECKONING_HPP

#include <numbers>
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
    // Default constructor.
    DeadReckoning() = default;

    // Constructor with initial motion.
    DeadReckoning(MotionType initialMotion)
    : TrajectoryPlanner<MotionType, AngleType, DistanceType, LinearVelocityType, AngularVelocityType>(
        initialMotion,
        0,
        0,
        {0, 0, 0},
        {0, 0, 0}) {}

    auto computeTrajectory(LinearVelocityType const& linearSpeed,
                           AngularVelocityType const& angularSpeed) -> void override final {
        // Extract values.
        double linear = std::get<0>(linearSpeed);
        double angular = std::get<2>(angularSpeed);

        // Ceil given speed values.
        linear = linear < models::ePuck.maxLinearSpeed ? linear : models::ePuck.maxLinearSpeed;
        angular = angular < models::ePuck.maxAngularSpeed ? angular : models::ePuck.maxAngularSpeed;

        // Check motion type.
        switch (this->motion_) {
        case 'L':
            this->distance_ = 0;
            this->linearVelocity_ = {0, 0, 0};
            this->angle_ = std::numbers::pi / 2;
            this->angularVelocity_ = {0, 0, angular};
            break;
        case 'R':
            this->distance_ = 0;
            this->linearVelocity_ = {0, 0, 0};
            this->angle_ = -std::numbers::pi / 2;
            this->angularVelocity_ = {0, 0, angular};
            break;
        case 'F':
            this->distance_ = models::maze.distanceBetweenCells;
            this->linearVelocity_ = {linear, 0, 0};
            this->angle_ = 0;
            this->angularVelocity_ = {0, 0, 0};
            break;
        case '\0':
            this->distance_ = 0;
            this->linearVelocity_ = {0, 0, 0};
            this->angle_ = 0;
            this->angularVelocity_ = {0, 0, 0};
            break;
        default: throw std::runtime_error("Invalid motion.");
        }
    }

   private:
    auto print(std::ostream& os) const noexcept -> void override final {
        os << "Angle: " << this->angle_ << "\t";
        os << "Distance: " << this->distance_ << "\t";
        os << "Linear Velocity: (" << std::get<0>(this->linearVelocity_) << ", "
           << std::get<1>(this->linearVelocity_) << ", " << std::get<2>(this->linearVelocity_)
           << ")\t";
        os << "Angular Velocity: (" << std::get<0>(this->angularVelocity_) << ", "
           << std::get<1>(this->angularVelocity_) << ", " << std::get<2>(this->angularVelocity_)
           << ")";
        os << std::endl;
    }
};
}  // namespace mtrn4110

#endif  // DEAD_RECKONING_HPP