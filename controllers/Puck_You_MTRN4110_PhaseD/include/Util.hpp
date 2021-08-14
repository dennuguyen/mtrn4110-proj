#ifndef UTIL_HPP
#define UTIL_HPP

#include <array>
#include <tuple>
#include <utility>
#include <vector>

namespace mtrn4110 {

constexpr std::array<char, 4> cardinalPoints = {'N', 'E', 'S', 'W'};

namespace defaultTypes {
using HeadingType = int;  // N, E, S, W
using PoseType = std::pair<int, int>;  // Coordinates.
using DistanceType = double;  // metres
using AngleType = double;  // degrees
using LinearVelocityType = std::tuple<double, double, double>;  // (x, y, z)
using AngularVelocityType = std::tuple<double, double, double>;  // (roll, pitch, yaw)
using MotionType = char;  // F, L, R
using PathType = std::vector<MotionType>;
using GraphType = std::vector<std::vector<int>>;  // Adjacency matrix of ints.
}  // namespace defaultTypes

namespace files {
constexpr auto csvPath = "../../MotionExecution.csv";  // Path to output Phase A execution.
constexpr auto motionPlanPath = "../../MotionPlan.txt";  // Path to read Phase A motion sequence.
constexpr auto mapPath = "../../Map.txt";  // Path to read in map for Phase B.
constexpr auto outputPath = "../../Output.txt";  // Path to output Phase B execution.
constexpr auto pathPlanPath = "../../PathPlan.txt";  // Path to output Phase B motion sequence.
}  // namespace files
}  // namespace mtrn4110

#endif  // UTIL_HPP