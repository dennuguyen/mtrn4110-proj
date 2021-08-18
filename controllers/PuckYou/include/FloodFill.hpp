#ifndef FLOOD_FILL_HPP
#define FLOOD_FILL_HPP

#include "PathPlanner.hpp"
#include "Util.hpp"

namespace mtrn4110 {
// Implementation of path planner interface using flood filling.
template<typename PoseType = defaultTypes::PoseType,
         typename HeadingType = defaultTypes::HeadingType,
         typename MotionType = defaultTypes::MotionType,
         typename GraphType = defaultTypes::GraphType>
class FloodFill final : public PathPlanner<PoseType, HeadingType, MotionType, GraphType> {
   public:
    // Enumerates the in and out directions
    enum Direction { UP, DOWN, LEFT, RIGHT, NIL };

    // A step of the path
    class Step {
       public:
        // ADD PUBLIC STUFF HERE
        int row;
        int col;
        int distance;
        Direction inDirection;
        Direction outDirection;

       private:
        // ADD PRIVATE STUFF HERE
    };

    // A path to the target
    class Path {
       public:
        // ADD PUBLIC STUFF HERE
        std::vector<Step> route;
        int numSteps;
        int numTurns;
        std::string pathString;

       private:
        // ADD PRIVATE STUFF HERE
    };

    FloodFill(GraphType graph, PoseType destination, PoseType initialPose, HeadingType initialHeading)
    : PathPlanner<PoseType, HeadingType, MotionType, GraphType>(graph,
                                                                destination,
                                                                initialPose,
                                                                initialHeading) {}

    // Flood fills the input map
    auto floodFill() -> void {
        // get target position from the maps
        int destinationRow = destination_.first;
        int destinationCol = destination_.second;
        // set target as step 0
        graph_[destinationRow][destinationCol].distance = 0;
        // while loop to flood fill
        bool finished = false;
        int step = 0;
        while (!finished) {
            finished = true;
            // looping through the grid
            for (int row = 0; row < models::maze.nRows; row++) {
                for (int col = 0; col < models::maze.nCols; col++) {
                    Node* current = &graph_[row][col];
                    // if node is at current step
                    if (current->distance == step) {
                        finished = false;
                        // fill up nodes
                        if (current->up) {
                            Node* up = &graph_[row - 1][col];
                            if (up->distance > step + 1) {
                                up->distance = step + 1;
                            }
                        }
                        // fill down nodes
                        if (current->down) {
                            Node* down = &graph_[row + 1][col];
                            if (down->distance > step + 1) {
                                down->distance = step + 1;
                            }
                        }
                        // fill left nodes
                        if (current->left) {
                            Node* left = &graph_[row][col - 1];
                            if (left->distance > step + 1) {
                                left->distance = step + 1;
                            }
                        }
                        // fill right nodes
                        if (current->right) {
                            Node* right = &graph_[row][col + 1];
                            if (right->distance > step + 1) {
                                right->distance = step + 1;
                            }
                        }
                    }
                }
            }
            step++;
        }
    }

    // Finds shortest paths to the destination
    auto processPaths() -> void {
        std::vector<Path> completePaths;
        std::vector<Path> incompletePaths;

        int startRow = initialPose_.first;
        int startCol = initialPose_.second;
        Node* start = &graph_[startRow][startCol];

        Path path;
        path.numSteps = start->distance;
        path.pathString = std::to_string(startRow) + std::to_string(startCol);

        // determine the starting direction
        Direction inDirection = NIL;
        switch (initialHeading_) {
        case NORTH:  // TODO: fix according to direction
            inDirection = DOWN;
            path.pathString += "N";
            break;
        case EAST:  // TODO: fix according to direction
            inDirection = LEFT;
            path.pathString += "E";
            break;
        case SOUTH:  // TODO: fix according to direction
            inDirection = UP;
            path.pathString += "S";
            break;
        case WEST:  // TODO: fix according to direction
            inDirection = RIGHT;
            path.pathString += "W";
            break;
        default:  // TODO: throw error
            break;
        }

        addNextStep(&incompletePaths, path, startRow, startCol, inDirection, NIL);

        while (!incompletePaths.empty()) {
            Path path = incompletePaths.front();
            incompletePaths.erase(incompletePaths.begin());

            // get the last step in the path
            Step* step = &path.route.back();
            int row = step->row;
            int col = step->col;
            int distance = step->distance;

            // the path is complete
            if (distance == 0) {
                completePaths.push_back(path);
                continue;
            }

            Node* current = &graph_[row][col];
            // if the upwards cell has a smaller step
            if (current->up && graph_[row - 1][col].distance < distance) {
                step->outDirection = UP;
                addNextStep(&incompletePaths, path, row - 1, col, DOWN, NIL);
            }
            // if the downwards cell has a smaller step
            if (current->down && graph_[row + 1][col].distance < distance) {
                step->outDirection = DOWN;
                addNextStep(&incompletePaths, path, row + 1, col, UP, NIL);
            }
            // if the leftwards cell has a smaller step
            if (current->left && graph_[row][col - 1].distance < distance) {
                step->outDirection = LEFT;
                addNextStep(&incompletePaths, path, row, col - 1, RIGHT, NIL);
            }
            // if the rightwards cell has a smaller step
            if (current->right && graph_[row][col + 1].distance < distance) {
                step->outDirection = RIGHT;
                addNextStep(&incompletePaths, path, row, col + 1, LEFT, NIL);
            }
        }
        paths_ = completePaths;
    }

    // Finds the final path
    auto findFinalPath() -> void {
        Path finalPath;
        int minTurns = INT_MAX;
        for (std::vector<Path>::iterator i = paths_.begin(); i != paths_.end(); ++i) {
            for (std::vector<Step>::iterator j = i->route.begin(); j != i->route.end(); ++j) {
                if (j->distance != 0) {
                    Direction inDirection = j->inDirection;
                    Direction outDirection = j->outDirection;
                    i->numTurns += numTurns[inDirection][outDirection];
                    i->pathString += turnString[inDirection][outDirection];
                }
            }
            i->route.erase(i->route.begin());
            if (i->numTurns < minTurns) {
                minTurns = i->numTurns;
                finalPath = *i;
            }
        }
        finalPath_ = finalPath;
    }

    // Gets the steps of the final path
    auto getFinalPathSteps() -> int {
        return finalPath_.route.front().distance + finalPath_.numTurns;
    }

   private:
    // ADD ANY PRIVATE METHODS BELOW HERE
    auto print(std::ostream& os) const noexcept -> void override final {}

    // Adds the next step to the path
    auto
    addNextStep(std::vector<Path>* paths, Path path, int row, int col, Direction in, Direction out)
        -> void {
        Step nextStep = {row, col, graph_[row][col].distance, in, out};
        path.route.push_back(nextStep);
        paths->push_back(path);
    }

    // ADD ANY PRIVATE MEMBERS BELOW HERE

    // Determines the number of turns
    static constexpr int numTurns[4][4] = {{2, 0, 1, 1}, {0, 2, 1, 1}, {1, 1, 2, 0}, {1, 1, 0, 2}};

    // Determines the string for turns
    static constexpr std::string turnString[4][4] = {{"LLF", "F", "RF", "LF"},
                                                     {"F", "LLF", "LF", "RF"},
                                                     {"LF", "RF", "LLF", "F"},
                                                     {"RF", "LF", "F", "LLF"}};

    // Holds all the shortest paths
    std::vector<Path> paths_;

    // Holds the final path
    Path finalPath_;
};
}  // namespace mtrn4110

#endif  // FLOOD_FILL_HPP