#ifndef UTIL_HPP
#define UTIL_HPP

#include <array>
#include <map>
#include <numeric>
#include <regex>
#include <tuple>
#include <utility>
#include <vector>

namespace mtrn4110 {

auto constexpr cardinalPoints = std::array<char, 4>({'N', 'E', 'S', 'W'});
auto constexpr unvisited = std::numeric_limits<int>::max();

namespace util {
// Tokenise the string by delimiter.
auto tokenise(std::string const& str, char const& delimiter) -> std::vector<std::string> {
    auto const regex_delimiter = std::regex("\n");
    return std::vector<std::string>(
        std::sregex_token_iterator(str.begin(), str.end(), regex_delimiter, -1),
        std::sregex_token_iterator());
}
}  // namespace util

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
auto constexpr mazeImage = "Maze.png";
auto constexpr ladybugImage = "../../images/Ladybug_small.png";
auto constexpr mouseImage = "../../images/mouse.png";
}  // namespace files
}  // namespace mtrn4110

#endif  // UTIL_HPP