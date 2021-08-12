#ifndef UTIL_HPP
#define UTIL_HPP

#include <map>
#include <utility>
#include <vector>

#include "Node.hpp"

const int N_ROWS = 5;
const int N_COLS = 9;

namespace mtrn4110 {
namespace defaultType {
using HeadingType = int;
using PoseType = std::pair<int, int>;
using VelocityType = double;
using MotionType = std::pair<PoseType, VelocityType>;
using GraphType = std::array<std::array<Node, N_COLS>, N_ROWS>;
}  // namespace defaultType

namespace file {
constexpr auto csvPath = "../../MotionExecution.csv";
constexpr auto mapPath = "../../Map.txt";
constexpr auto pathPlanPath = "../../PathPlan.txt";
}  // namespace file
}  // namespace mtrn4110

#endif  // UTIL_HPP