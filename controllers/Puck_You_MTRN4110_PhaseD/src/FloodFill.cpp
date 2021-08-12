#include "FloodFill.hpp"

const int N_TURNS[4][4] =
{
    {2, 0, 1, 1},
    {0, 2, 1 ,1},
    {1, 1, 2, 0},
    {1, 1, 0, 2}
};

static const std::string TURN_STRING[4][4] =
{
    {"LLF", "F",   "RF",  "LF"},
    {"F",   "LLF", "LF" , "RF"},
    {"LF",  "RF",  "LLF", "F"},
    {"RF",  "LF",  "F",   "LLF"}
};

namespace mtrn4010 {

FloodFill::FloodFill(GraphType graph, PoseType destination, PoseType initialPose, HeadingType initialHeading)
    : PathPlanner(graph, destination, initialPose, initialHeading) {}

auto FloodFill::floodfill() {
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
        for (int row = 0; row < N_ROWS; row++) {
            for (int col = 0; col < N_COLS; col++) {
                Node *current = &graph_[row][col];
                // if node is at current step
                if (current->distance == step) {
                    finished = false;
                    // fill up nodes
                    if (current->up) {
                        Node *up = &graph_[row - 1][col];
                        if (up->distance > step + 1) {
                            up->distance = step + 1;
                        }
                    }
                    // fill down nodes
                    if (current->down) {
                        Node *down = &graph_[row + 1][col];
                        if (down->distance > step + 1) {
                            down->distance = step + 1;
                        }
                    }
                    // fill left nodes
                    if (current->left) {
                        Node *left = &graph_[row][col - 1];
                        if (left->distance > step + 1) {
                            left->distance = step + 1;
                        }
                    }
                    // fill right nodes
                    if (current->right) {
                        Node *right = &graph_[row][col + 1];
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

auto FloodFill::processPaths() {
    std::vector<Path> completePaths;
    std::vector<Path> incompletePaths;

    int startRow = currentPose_.first;
    int startCol = currentPose_.second;
    Node *start = &graph_[startRow][startCol];

    Path path;
    path.numSteps = start->distance;
    path.pathString = std::to_string(startRow) + std::to_string(startCol);

    // determine the starting direction
    Direction inDirection = NIL;
    switch (currentHeading_) {
    case NORTH:
        inDirection = DOWN;
        path.pathString += "N";
        break;
    case EAST:
        inDirection = LEFT;
        path.pathString += "E";
        break;
    case SOUTH:
        inDirection = UP;
        path.pathString += "S";
        break;
    case WEST:
        inDirection = RIGHT;
        path.pathString += "W";
        break;
    default:
        break;
    }

    addNextStep(&incompletePaths, path, startRow, startCol, inDirection, NIL);

    while (!incompletePaths.empty()) {
        Path path = incompletePaths.front();
        incompletePaths.erase(incompletePaths.begin());

        // get the last step in the path
        Step *step = &path.route.back();
        int row = step->row;
        int col = step->col;
        int distance = step->distance;

        // the path is complete
        if (distance == 0) {
            completePaths.push_back(path);
            continue;
        }

        Node *current = &graph_[row][col];
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

auto FloodFill::addNextStep(std::vector<Path> *paths, Path path, int row, int col, Direction in, Direction out) {
    Step nextStep = {row, col, graph_[row][col].distance, in, out};
    path.route.push_back(nextStep);
    paths->push_back(path);
}

auto FloodFill::findFinalPath() {
    Path finalPath;
    int minTurns = INT_MAX;
    for (std::vector<Path>::iterator i = paths_.begin(); i != paths_.end(); ++i) {
        for (std::vector<Step>::iterator j = i->route.begin(); j != i->route.end(); ++j) {
            if (j->distance != 0) {
                Direction inDirection = j->inDirection;
                Direction outDirection = j->outDirection;
                i->numTurns += N_TURNS[inDirection][outDirection];
                i->pathString += TURN_STRING[inDirection][outDirection];
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

}   // namespace mtrn4110


