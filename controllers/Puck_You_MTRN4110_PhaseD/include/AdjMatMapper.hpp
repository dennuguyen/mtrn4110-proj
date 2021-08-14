#ifndef ADJ_MAT_MAPPER_HPP
#define ADJ_MAT_MAPPER_HPP

#include <limits>

#include "Mapper.hpp"
#include "Models.hpp"
#include "Node.hpp"

namespace mtrn4110 {
// Implementation of mapper interface to create a graph represented by an adjacency matrix.
template<typename PoseType = defaultTypes::PoseType,
         typename HeadingType = defaultTypes::HeadingType,
         typename GraphType = std::vector<std::vector<Node>>>
class AdjMatMapper final : public Mapper<GraphType> {
   public:
    AdjMatMapper()
    : Mapper<GraphType>() {}

    // Reads the input stream which has the map.
    auto readMap(std::istream& inputStream) -> void override final {
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

    // Builds the map from read inputs
    auto buildGraph() -> void override final {
        firstParse();
        secondParse();
    }

   private:
    auto print(std::ostream& os) const noexcept -> void override final {}

    // Extracts vertical and horizontal wall information from the map.
    auto firstParse() -> void {
        for (int lineNumber = 0; lineNumber < maxLines; lineNumber++) {
            // Determine the row
            int row = lineNumber / 2;
            // Determine is line is for horizontal or vertical walls
            if (lineNumber % 2 == 0) {
                extractHorizontalLine(map_[lineNumber], row);
            }
            else {
                extractVerticalLine(map_[lineNumber], row);
            }
        }
    }

    // Extract information from line for horizontal walls.
    auto extractHorizontalLine(std::string line, int row) -> void {
        // extracting horizontal walls
        for (int i = 1; i < static_cast<int>(line.size()) && i < maxChars; i += cellSize) {
            // calculating column
            int col = i / cellSize;
            // detecting walls
            if (line[i] == hWall) {
                horizontalWalls_[row][col] = true;
            }
            else {
                horizontalWalls_[row][col] = false;
            }
        }
    }

    // Extract information from line for vertical walls.
    auto extractVerticalLine(std::string line, int row) -> void {
        // extracting vertical walls
        for (int i = 0; i < static_cast<int>(line.size()) && i < maxChars; i++) {
            // calculating column
            int col = i / cellSize;
            // detecting walls
            if (i % cellSize == 0) {
                if (line[i] == vWall) {
                    verticalWalls_[row][col] = true;
                }
                else {
                    verticalWalls_[row][col] = false;
                }
            }
            // for robot start or target
            switch (line[i]) {
            case north:
                initialHeading_ = north;  // TODO: might need updating
                initialPose_ = {row, col};
                break;
            case east:
                initialHeading_ = east;  // TODO: might need updating
                initialPose_ = {row, col};
                break;
            case south:
                initialHeading_ = south;  // TODO: might need updating
                initialPose_ = {row, col};
                break;
            case west:
                initialHeading_ = west;  // TODO: might need updating
                initialPose_ = {row, col};
                break;
            case target: destination_ = {row, col}; break;
            default: break;
            }
        }
    }

    auto secondParse() -> void {
        for (int row = 0; row < models::maze.nRows; row++) {
            for (int col = 0; col < models::maze.nCols; col++) {
                // checking upwards connections
                if (!horizontalWalls_[row][col]) {
                    this->graph_[row][col].up = true;
                }
                else {
                    this->graph_[row][col].up = false;
                }
                // checking downwards connections
                if (!horizontalWalls_[row + 1][col]) {
                    this->graph_[row][col].down = true;
                }
                else {
                    this->graph_[row][col].down = false;
                }
                // checking leftwards connections
                if (!verticalWalls_[row][col]) {
                    this->graph_[row][col].left = true;
                }
                else {
                    this->graph_[row][col].left = false;
                }
                // checking rightwards connections
                if (!verticalWalls_[row][col + 1]) {
                    this->graph_[row][col].right = true;
                }
                else {
                    this->graph_[row][col].right = false;
                }
                // default values
                this->graph_[row][col].row = row;
                this->graph_[row][col].col = col;
                this->graph_[row][col].distance = std::numeric_limits<int>::max();
            }
        }
    }

    static constexpr char north = '^';
    static constexpr char east = '>';
    static constexpr char south = 'v';
    static constexpr char west = '<';
    static constexpr char target = 'x';
    static constexpr char hWall = '-';
    static constexpr char vWall = '|';
    static constexpr int cellSize = 4;
    static const int maxChars = models::maze.nCols * cellSize + 1;
    static const int maxLines = 2 * models::maze.nRows + 1;
    std::vector<std::string> map_;
    std::array<std::array<bool, models::maze.nCols>, models::maze.nRows + 1> horizontalWalls_;
    std::array<std::array<bool, models::maze.nCols + 1>, models::maze.nRows> verticalWalls_;
    PoseType initialPose_;
    PoseType destination_;
    HeadingType initialHeading_;
};
}  // namespace mtrn4110

#endif  // ADJ_MAT_MAPPER_HPP