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
constexpr auto csvOutput = "../../MotionExecution.csv";
constexpr auto motionSequenceText = "../../MotionPlan.txt";
constexpr auto mapText = "../../Map.txt";
constexpr auto mazeImage = "../../images/Maze_2.png";
constexpr auto robotImage = "../../Robot_2.png";
constexpr auto ladybugImage = "../Ladybug_small.png";
}  // namespace files

namespace colours {
constexpr auto cyan = {255, 0, 255};
constexpr auto magenta = {0, 255, 255};
constexpr auto birch = {120, 50, 255};
constexpr auto epuck = {150, 20, 20};
constexpr auto red = {0, 255, 0};
}  // namespace colours
}  // namespace mtrn4110

#endif  // UTIL_HPP