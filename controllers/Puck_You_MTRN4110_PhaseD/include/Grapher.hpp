#ifndef GRAPHER_HPP
#define GRAPHER_HPP

#include <map>

#include "Util.hpp"

namespace mtrn4110 {
// An interface for a generic grapher.
template<typename MapType = defaultTypes::MapType, typename GraphType = defaultTypes::GraphType>
class Grapher {
   public:
    class Graph {
       public:
       private:
    };

    // Constructor to initialise graph.
    Grapher()
    : map_() {}

    // Read the map from the input stream.
    auto readMap(std::istream& inputStream) -> void {
        if (inputStream.good() == false) {
            throw std::runtime_error("Could not open file.");
        }

        auto line = std::string();
        while (std::getline(inputStream, line)) {
            map_.push_back(line);
        }

        if (inputStream.good() == false) {
            throw std::runtime_error("I/O error while reading.");
        }
        if (inputStream.eof() == false) {
            throw std::runtime_error("Did not reach EOF.");
        }
    }

    // Build the graph from the read-in map.
    auto buildGraph() -> GraphType {
        if (map_.empty() == true) {
            throw std::runtime_error("Cannot build graph from empty map.");
        }

        auto graph =
            std::map<std::pair<int, int>, std::pair<int, std::vector<std::pair<int, int>>>>();

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
                    // case 'x': end_ = {x, y}; break;
                    // case '^':
                    //     initialHeading_ = 0;
                    //     start_ = {x, y};
                    //     break;
                    // case '>':
                    //     initialHeading_ = 1;
                    //     start_ = {x, y};
                    //     break;
                    // case 'v':
                    //     initialHeading_ = 2;
                    //     start_ = {x, y};
                    //     break;
                    // case '<':
                    //     initialHeading_ = 3;
                    //     start_ = {x, y};
                    //     break;
                    default: throw std::runtime_error("Invalid map character");
                    }

                    // Check vertical wall to right of centre of tile.
                    if (col + 2 < maxColumn) {
                        if (map_[line][col + 2] == ' ') {
                            graph[{x, y}].first = unvisited;
                            graph[{x, y}].second.emplace_back(x + 1, y);
                            graph[{x + 1, y}].first = unvisited;
                            graph[{x + 1, y}].second.emplace_back(x, y);
                        }
                    }

                    // Check horizontal wall below centre of tile.
                    if (line + 1 < maxLine) {
                        if (map_[line + 1][col] == ' ') {
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

    // Operator overload for <<.
    friend auto operator<<(std::ostream& os, Grapher const& grapher) noexcept -> std::ostream& {
        grapher.print(os);
        return os;
    }

   protected:
    MapType map_;

   private:
    // Write any required data to an output stream.
    auto print(std::ostream& os) const noexcept -> void {}

    static auto constexpr unvisited = -1;
};
}  // namespace mtrn4110

#endif  // GRAPHER_HPP