#ifndef UTIL_HPP
#define UTIL_HPP

#include <map>
#include <utility>
#include <vector>

namespace mtrn4110 {
namespace defaultTypes {
using PoseType = std::pair<int, int>;
using VelocityType = double;
using MotionType = std::pair<PoseType, VelocityType>;
using GraphType = std::map<PoseType, std::pair<int, std::vector<PoseType>>>;
}  // namespace defaultTypes
}  // namespace mtrn4110

#endif  // UTIL_HPP