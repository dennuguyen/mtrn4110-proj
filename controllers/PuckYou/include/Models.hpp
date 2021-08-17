#ifndef MODELS_HPP
#define MODELS_HPP

namespace mtrn4110 {
namespace models {
// Struct outlining the properties of a map.
struct MapModel {
    constexpr MapModel(double distanceBetweenCells, int nRows, int nCols)
    : distanceBetweenCells(distanceBetweenCells)
    , nRows(nRows)
    , nCols(nCols) {}

    double const distanceBetweenCells;  // m
    int const nRows;
    int const nCols;
};

// Struct outlining the properties of a robot.
struct RobotModel {
    constexpr RobotModel(double diameter,
                         double height,
                         double wheelRadius,
                         double axleLength,
                         double mass,
                         double maxLinearSpeed,
                         double maxAngularSpeed,
                         double maxMotorSpeed)
    : diameter(diameter)
    , height(height)
    , wheelRadius(wheelRadius)
    , axleLength(axleLength)
    , mass(mass)
    , maxLinearSpeed(maxLinearSpeed)
    , maxAngularSpeed(maxAngularSpeed)
    , maxMotorSpeed(maxMotorSpeed) {}

    double const diameter;  // m
    double const height;  // m
    double const wheelRadius;  // m
    double const axleLength;  // m
    double const mass;  // kg
    double const maxLinearSpeed;  // m/s
    double const maxAngularSpeed;  // rad/s
    double const maxMotorSpeed;  // rad/s
};

// Maze model.
constexpr auto maze = MapModel(0.165, 5, 9);

// EPuck model.
constexpr auto ePuck = RobotModel(0.071, 0.05, 0.02, 0.0566, 0.16, 0.1256, 4.438, 6.28);

}  // namespace models
}  // namespace mtrn4110

#endif  // MODELS_HPP