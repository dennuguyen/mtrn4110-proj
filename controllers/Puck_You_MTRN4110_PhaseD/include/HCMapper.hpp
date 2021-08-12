#ifndef HC_MAPPER_HPP
#define HC_MAPPER_HPP

#include "Mapper.hpp"
#include "Models.hpp"

namespace mtrn4110 {
// Implementation of mapper interface using a hard-coded algorithm.
template<typename PoseType = defaultTypes::PoseType,
         typename HeadingType = defaultTypes::HeadingType,
         typename GraphType = defaultTypes::GraphType>
class HCMapper : public Mapper<GraphType> {
   public:
    HCMapper()
    : Mapper<GraphType>(models::maze.nCols) {}  // EDIT CONSTRUCTOR PARAMETERS AS REQUIRED

    // ADD ANY PUBLIC METHODS BELOW HERE

    // Reads the map file
    auto readMap() -> void {
        auto mapFile = std::ifstream(files::mapPath);
        if (mapFile.good() == false) {
            throw std::runtime_error("Could not open file.");
        }

        auto line = std::string();
        while (std::getline(mapFile, line)) {
            map_.push_back(line);
        }

        if (mapFile.bad() == true) {
            throw std::runtime_error("I/O error while reading.");
        }
        if (mapFile.eof() == false) {
            throw std::runtime_error("Did not reach EOF.");
        }
    }

    // Extracts information from the map
    auto extractMap() -> void {
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

    // Builds the map from read inputs
    auto buildMap() -> void {
        for (int row = 0; row < models::maze.nRows; row++) {
            for (int col = 0; col < models::maze.nCols; col++) {
                // checking upwards connections
                if (!horizontalWalls_[row][col]) {
                    graph_[row][col].up = true;
                }
                else {
                    graph_[row][col].up = false;
                }
                // checking downwards connections
                if (!horizontalWalls_[row + 1][col]) {
                    graph_[row][col].down = true;
                }
                else {
                    graph_[row][col].down = false;
                }
                // checking leftwards connections
                if (!verticalWalls_[row][col]) {
                    graph_[row][col].left = true;
                }
                else {
                    graph_[row][col].left = false;
                }
                // checking rightwards connections
                if (!verticalWalls_[row][col + 1]) {
                    graph_[row][col].right = true;
                }
                else {
                    graph_[row][col].right = false;
                }
                // default values
                graph_[row][col].row = row;
                graph_[row][col].col = col;
                graph_[row][col].distance = INT_MAX;
            }
        }
    }

   private:
    // ADD ANY PRIVATE METHODS BELOW HERE
    auto print(std::ostream& os) const noexcept -> void override final {}

    // Extract information from line for horizontal walls
    auto extractHorizontalLine(std::string line, int row) -> void final {
        // extracting horizontal walls
        for (int i = 1; i < line.size() && i < maxChars; i += cellSize) {
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

    // Extract information from line for vertical walls
    auto extractVerticalLine(std::string line, int row) -> void final {
        // extracting vertical walls
        for (int i = 0; i < line.size() && i < maxChars; i++) {
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

    // ADD ANY PRIVATE MEMBERS BELOW HERE
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

#endif  // HC_MAPPER_HPP