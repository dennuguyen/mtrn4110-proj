#ifndef GRAPHER_HPP
#define GRAPHER_HPP

#include <map>

#include "Util.hpp"

namespace mtrn4110 {
// An interface for a grapher.
template<typename GraphType = defaultTypes::GraphType>
class Grapher {
   public:
    // Default constructor.
    Grapher() = default;

    // Build the graph from the read-in map.
    auto buildGraph(std::string const& map) -> GraphType {
        if (map.empty() == true) {
            throw std::runtime_error("Cannot build graph from empty map.");
        }

        // Tokenise the map string for [][] access operator.
        auto tokenisedMap = util::tokenise(map, '\n');

        auto graph = GraphType();
        auto const& maxLine = static_cast<int>(tokenisedMap.size());
        auto const& maxColumn = static_cast<int>(tokenisedMap.at(0).size());
        for (auto line = 0; line < maxLine; line++) {
            for (auto col = 0; col < maxColumn; col++) {
                // At centre of tile.
                if ((col + 2) % 4 == 0 && line % 2 != 0) {
                    auto const x = (col - 2) / 4;
                    auto const y = (line - 1) / 2;

                    // Check vertical wall to right of centre of tile.
                    if (col + 2 < maxColumn) {
                        if (tokenisedMap[line][col + 2] == ' ') {
                            graph[{x, y}].first = unvisited;
                            graph[{x, y}].second.emplace_back(x + 1, y);
                            graph[{x + 1, y}].first = unvisited;
                            graph[{x + 1, y}].second.emplace_back(x, y);
                        }
                    }

                    // Check horizontal wall below centre of tile.
                    if (line + 1 < maxLine) {
                        if (tokenisedMap[line + 1][col] == ' ') {
                            graph[{x, y}].first = unvisited;
                            graph[{x, y}].second.emplace_back(x, y + 1);
                            graph[{x, y + 1}].first = unvisited;
                            graph[{x, y + 1}].second.emplace_back(x, y);
                        }
                    }
                }
            }
        }
        return graph;
    }
};
}  // namespace mtrn4110

#endif  // GRAPHER_HPP