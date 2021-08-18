#ifndef GRAPHER_HPP
#define GRAPHER_HPP

#include <map>

#include "Util.hpp"

namespace mtrn4110 {
// An interface for a grapher.
template<typename MapType = defaultTypes::MapType, typename GraphType = defaultTypes::GraphType>
class Grapher {
   public:
    // Default constructor.
    Grapher() = default;

    // Build the graph from the read-in map.
    auto buildGraph(MapType map) -> GraphType {
        if (map.empty() == true) {
            throw std::runtime_error("Cannot build graph from empty map.");
        }

        auto graph = GraphType();
        auto const& maxLine = static_cast<int>(map.size());
        auto const& maxColumn = static_cast<int>(map.at(0).size());
        for (auto line = 0; line < maxLine; line++) {
            for (auto col = 0; col < maxColumn; col++) {
                // At centre of tile.
                if ((col + 2) % 4 == 0 && line % 2 != 0) {
                    auto const x = (col - 2) / 4;
                    auto const y = (line - 1) / 2;

                    // Check vertical wall to right of centre of tile.
                    if (col + 2 < maxColumn) {
                        if (map[line][col + 2] == ' ') {
                            graph[{y, x}].first = unvisited;
                            graph[{y, x}].second.emplace_back(y, x + 1);
                            graph[{y, x + 1}].first = unvisited;
                            graph[{y, x + 1}].second.emplace_back(y, x);
                        }
                    }

                    // Check horizontal wall below centre of tile.
                    if (line + 1 < maxLine) {
                        if (map[line + 1][col] == ' ') {
                            graph[{y, x}].first = unvisited;
                            graph[{y, x}].second.emplace_back(y + 1, x);
                            graph[{y + 1, x}].first = unvisited;
                            graph[{y + 1, x}].second.emplace_back(y, x);
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