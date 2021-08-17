#ifndef TRAJECTORY_PLANNER_HPP
#define TRAJECTORY_PLANNER_HPP

#include "Util.hpp"

namespace mtrn4110 {
// An interface for a generic trajectory planner.
template<typename MotionType = defaultTypes::MotionType,
         typename AngleType = defaultTypes::AngleType,
         typename DistanceType = defaultTypes::DistanceType,
         typename LinearVelocityType = defaultTypes::LinearVelocityType,
         typename AngularVelocityType = defaultTypes::AngularVelocityType>
class TrajectoryPlanner {
   public:
    // Default constructor.
    TrajectoryPlanner() = default;

    // Initialise the trajectory planner with initial motion, distance, linear velocity, and angular
    // velocity.
    TrajectoryPlanner(MotionType motion,
                      AngleType angle,
                      DistanceType distance,
                      LinearVelocityType linearVelocity,
                      AngularVelocityType angularVelocity)
    : motion_(motion)
    , angle_(angle)
    , distance_(distance)
    , linearVelocity_(linearVelocity)
    , angularVelocity_(angularVelocity) {}

    // Update the motion. It is up to the user to keep track of the progress of each motion.
    auto updateMotion(MotionType motion) noexcept -> void {
        motion_ = motion;
    }

    auto getCurrentMotion() const noexcept -> MotionType {
        return motion_;
    }

    auto getAngle() const noexcept -> AngleType {
        return angle_;
    }

    auto getDistance() const noexcept -> DistanceType {
        return distance_;
    }

    auto getLinearVelocity() const noexcept -> LinearVelocityType {
        return linearVelocity_;
    }

    auto getAngularVelocity() const noexcept -> AngularVelocityType {
        return angularVelocity_;
    }

    // Operator overload for <<.
    friend auto operator<<(std::ostream& os, TrajectoryPlanner const& trajectoryPlanner) noexcept
        -> std::ostream& {
        trajectoryPlanner.print(os);
        return os;
    }

   protected:
    MotionType motion_;  // High-level representation of the motion the robot will follow.
    AngleType angle_;  // Robot angular travel.
    DistanceType distance_;  // Robot travel distance.
    LinearVelocityType linearVelocity_;  // Robot linear velocity.
    AngularVelocityType angularVelocity_;  // Robot angular velocity.

   private:
    // Compute the distance and velocities from the next and previous motions. It is up to the user
    // to update the motion if required.
    virtual auto computeTrajectory(LinearVelocityType const& linearSpeed,
                                   AngularVelocityType const& angularSpeed) -> void = 0;

    // Write any required data to an output stream.
    virtual auto print(std::ostream& os) const noexcept -> void = 0;
};
}  // namespace mtrn4110

#endif  // TRAJECTORY_PLANNER_HPP