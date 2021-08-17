#ifndef UTIL_HPP
#define UTIL_HPP

#include <array>
#include <tuple>
#include <utility>
#include <vector>

namespace mtrn4110 {

auto constexpr cardinalPoints = {'N', 'E', 'S', 'W'};
auto constexpr unvisited = -1;

namespace defaultTypes {
using HeadingType = int;  // N, E, S, W
using PoseType = std::pair<int, int>;  // Coordinates.
using DistanceType = double;  // metres
using AngleType = double;  // degrees
using LinearVelocityType = std::tuple<double, double, double>;  // (x, y, z)
using AngularVelocityType = std::tuple<double, double, double>;  // (roll, pitch, yaw)
using MotionType = char;  // F, L, R
using PathType = std::vector<MotionType>;
using MapType = std::vector<std::string>;
using GraphType =
    std::map<std::pair<int, int>, std::pair<int, std::vector<std::pair<int, int>>>>;  // DWG
}  // namespace defaultTypes

namespace files {
constexpr auto csvOutput = "../../MotionExecution.csv";
constexpr auto mazeImage = "Maze.png";
// constexpr auto robotImage = "../../images/Robot_2.png";
// constexpr auto ladybugImage = "../../images/Ladybug_small.png";
}  // namespace files
}  // namespace mtrn4110

#endif  // UTIL_HPP