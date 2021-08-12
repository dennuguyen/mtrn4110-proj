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
    RobotModel(double wheelRadius, double axleLength, double maxSpeed, double maxMotorSpeed)
    : wheelRadius(wheelRadius)
    , axleLength(axleLength)
    , maxSpeed(maxSpeed)
    , maxMotorSpeed(maxMotorSpeed) {}

    double const wheelRadius;  // m
    double const axleLength;  // m
    double const maxSpeed;  // m/s
    double const maxMotorSpeed;  // rad/s
};

auto maze = MapModel(0.165, 5, 9);
auto ePuck = RobotModel(0.02, 0.0566, 0.1287, 6.28);

}  // namespace models
}  // namespace mtrn4110

#endif  // MODELS_HPP