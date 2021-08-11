#ifndef KINEMATIC_MODEL_HPP
#define KINEMATIC_MODEL_HPP

namespace {
struct KinematicModel {
    KinematicModel(double wheelRadius, double axleLength, double maxSpeed, double maxMotorSpeed)
    : wheelRadius(wheelRadius)
    , axleLength(axleLength)
    , maxSpeed(maxSpeed)
    , maxMotorSpeed(maxMotorSpeed) {}

    double const wheelRadius;
    double const axleLength;
    double const maxSpeed;
    double const maxMotorSpeed;
};
}  // namespace

namespace mtrn4110 {
namespace model {
auto ePuck = KinematicModel(0.02, 0.0566, 0.1287, 6.28);
}  // namespace model
}  // namespace mtrn4110

#endif  // KINEMATIC_MODEL_HPP