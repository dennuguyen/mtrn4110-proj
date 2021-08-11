#ifndef UTIL_HPP
#define UTIL_HPP

#include <map>
#include <utility>
#include <vector>

namespace mtrn4110 {
namespace defaultType {
using HeadingType = int;
using PoseType = std::pair<int, int>;
using VelocityType = double;
using MotionType = char;  // F, L, R
using GraphType = std::map<PoseType, std::pair<int, std::vector<PoseType>>>;
}  // namespace defaultType

namespace file {
constexpr auto csvPath = "../../MotionExecution.csv";
constexpr auto mapPath = "../../Map.txt";
constexpr auto pathPlanPath = "../../PathPlan.txt";
}  // namespace file
}  // namespace mtrn4110

#endif  // UTIL_HPP