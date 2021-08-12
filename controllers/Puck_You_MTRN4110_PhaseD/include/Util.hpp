#ifndef UTIL_HPP
#define UTIL_HPP

#include <tuple>
#include <utility>
#include <vector>

#include "Node.hpp"

namespace mtrn4110 {

enum class Heading { N, E, S, W };

namespace defaultTypes {
using HeadingType = int;  // N, E, S, W
using PoseType = std::pair<int, int>;  // Coordinates.
using DistanceType = double;  // metres
using AngleType = double;  // degrees
using LinearVelocityType = std::tuple<double, double, double>;  // (x, y, z)
using AngularVelocityType = std::tuple<double, double, double>;  // (roll, pitch, yaw)
using MotionType = char;  // F, L, R
using GraphType = std::vector<std::vector<Node>>;
}  // namespace defaultTypes

namespace files {
constexpr auto csvPath = "../../MotionExecution.csv";
constexpr auto mapPath = "../../Map.txt";
constexpr auto pathPlanPath = "../../PathPlan.txt";
}  // namespace files
}  // namespace mtrn4110

#endif  // UTIL_HPP