#ifndef UTIL_HPP
#define UTIL_HPP

#include <map>
#include <utility>
#include <vector>

#include "Node.hpp"

const int N_ROWS = 5;
const int N_COLS = 9;

namespace mtrn4110 {
namespace defaultTypes {
using HeadingType = int;
using PoseType = std::pair<int, int>;
using DistanceType = double;  // metres
using AngleType = double;  // degrees
using LinearVelocityType = std::tuple<double, double, double>;  // (x, y, z)
using AngularVelocityType = std::tuple<double, double, double>;  // (roll, pitch, yaw)
using MotionType = char;  // F, L, R
using GraphType = std::array<std::array<Node, N_COLS>, N_ROWS>;
}  // namespace defaultTypes

namespace files {
constexpr auto csvPath = "../../MotionExecution.csv";
constexpr auto mapPath = "../../Map.txt";
constexpr auto pathPlanPath = "../../PathPlan.txt";
}  // namespace files
}  // namespace mtrn4110

#endif  // UTIL_HPP