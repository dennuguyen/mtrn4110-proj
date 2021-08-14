#ifndef HC_MAPPER_HPP
#define HC_MAPPER_HPP

#include <map>
#include <utility>

#include "Mapper.hpp"
#include "Models.hpp"

namespace mtrn4110 {
// Implementation of mapper interface to create a graph represented by an adjacency matrix.
template<typename PoseType = defaultTypes::PoseType,
         typename HeadingType = defaultTypes::HeadingType,
         typename GraphType =
             std::map<std::pair<int, int>, std::pair<int, std::vector<std::pair<int, int>>>>>
class HCMapper final : public Mapper<GraphType> {
   public:
    HCMapper()
    : Mapper<GraphType>(models::maze.nCols) {}

    // Reads the input stream which has the map.
    auto readMap(std::istream const& mapStream) -> void override final {
        if (mapStream.good() == false) {
            throw std::runtime_error("Could not open file.");
        }

        auto line = std::string();
        while (std::getline(mapStream, line)) {
            map_.push_back(line);
        }

        if (mapStream.good() == false) {
            throw std::runtime_error("I/O error while reading.");
        }
        if (mapStream.eof() == false) {
            throw std::runtime_error("Did not reach EOF.");
        }
    }

    // Build a graph from the map.
    auto buildGraph() -> void override final {
        firstParse();
        secondParse();
    }

   private:
    auto print(std::ostream& os) const noexcept -> void override final {}

    // Parses the map and extracts it into the adjacency list graph representation.
    auto firstParse() -> void {
        if (map_.empty() == true) {
            throw std::runtime_error("Cannot build graph from empty map.");
        }

        auto const& maxLine = static_cast<int>(map_.size());
        auto const& maxColumn = static_cast<int>(map_.at(0).size());
        for (auto line = 0; line < maxLine; line++) {
            for (auto col = 0; col < maxColumn; col++) {
                // At centre of tile.
                if ((col + 2) % 4 == 0 && line % 2 != 0) {
                    auto const x = (col - 2) / 4;
                    auto const y = (line - 1) / 2;

                    // Check start and end position.
                    switch (map_[line][col]) {
                    case ' ': break;
                    case 'x': end_ = {x, y}; break;
                    case '^':
                        initialHeading_ = 0;
                        start_ = {x, y};
                        break;
                    case '>':
                        initialHeading_ = 1;
                        start_ = {x, y};
                        break;
                    case 'v':
                        initialHeading_ = 2;
                        start_ = {x, y};
                        break;
                    case '<':
                        initialHeading_ = 3;
                        start_ = {x, y};
                        break;
                    default: throw std::runtime_error("Invalid map character");
                    }

                    // Check vertical wall to right of centre of tile.
                    if (col + 2 < maxColumn) {
                        if (map_[line][col + 2] == ' ') {
                            graph_[{x, y}].first = unvisited;
                            graph_[{x, y}].second.emplace_back(x + 1, y);
                            graph_[{x + 1, y}].first = unvisited;
                            graph_[{x + 1, y}].second.emplace_back(x, y);
                        }
                    }

                    // Check horizontal wall below centre of tile.
                    if (line + 1 < maxLine) {
                        if (map_[line + 1][col] == ' ') {
                            graph_[{x, y}].first = unvisited;
                            graph_[{x, y}].second.emplace_back(x, y + 1);
                            graph_[{x, y + 1}].first = unvisited;
                            graph_[{x, y + 1}].second.emplace_back(x, y);
                        }
                    }
                }
            }
        }
    }

    // Perform a BFS on the graph to get directedness of the graph from end_ to start_.
    auto secondParse() -> void {
        graph_.at(end_).first = 0;

        auto pathQueue = std::queue<std::pair<int, int>>();
        pathQueue.push(end_);

        while (pathQueue.empty() == false) {
            auto const currentPosition = pathQueue.front();
            pathQueue.pop();

            // Found the destination.
            if (currentPosition == start_) {
                break;
            }

            for (auto const& adjacentPosition : graph_.at(currentPosition).second) {
                // Give unvisited words a distance from source.
                if (graph_.at(adjacentPosition).first == unvisited) {
                    graph_.at(adjacentPosition).first = graph_.at(currentPosition).first + 1;
                    pathQueue.push(adjacentPosition);
                }
            }
        }
    }

    static auto constexpr unvisited = -1;
    const std::array<char, 4> cardinalPoints = {'N', 'E', 'S', 'W'};

    // Map is represented as a vector of string for the ease of use of [][] access operators.
    std::vector<std::string> map_;

    // Start position of path plan.
    PoseType start_;

    // End position of path plan.
    PoseType end_;

    // Initial heading represented as an index to cardinalPoints.
    HeadingType initialHeading_;  // N = 0, E = 1, S = 2, W = 3
};
}  // namespace mtrn4110

#endif  // HC_MAPPER_HPP