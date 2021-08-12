#ifndef MODELS_HPP
#define MODELS_HPP

namespace mtrn4110 {
namespace models {
// Struct outlining the properties of a map.
struct MapModel {
    MapModel(double distanceBetweenCells, int nRows, int nCols)
    : distanceBetweenCells(distanceBetweenCells)
    , nRows(nRows)
    , nCols(nCols) {}

    double const distanceBetweenCells;  // m
    int const nRows;
    int const nCols;
};

// Struct outlining the properties of a robot.
struct RobotModel {
    RobotModel(double diameter,
               double height,
               double wheelRadius,
               double axleLength,
               double mass,
               double maxSpeed,
               double maxMotorSpeed)
    : diameter(diameter)
    , height(height)
    , wheelRadius(wheelRadius)
    , axleLength(axleLength)
    , mass(mass)
    , maxSpeed(maxSpeed)
    , maxMotorSpeed(maxMotorSpeed) {}

    double const diameter;  // m
    double const height;  // m
    double const wheelRadius;  // m
    double const axleLength;  // m
    double const mass;  // kg
    double const maxSpeed;  // m/s
    double const maxMotorSpeed;  // rad/s
};

// Instantiations of above models.
// Maze model.
auto maze = MapModel(0.165, 5, 9);
// EPuck model.
auto ePuck = RobotModel(0.071, 0.05, 0.02, 0.0566, 0.16, 0.25, 6.28);

}  // namespace models
}  // namespace mtrn4110

#endif  // MODELS_HPP