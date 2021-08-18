#ifndef BFS_DFS_HPP
#define BFS_DFS_HPP

#include <algorithm>
#include <iterator>
#include <queue>
#include <stack>
#include <stdexcept>
#include <vector>

#include "PathPlanner.hpp"

namespace mtrn4110 {

// Implementation of the path planner interface which uses a BFS + DFS algorithm to find shortest
// path.
template<typename PoseType = defaultTypes::PoseType,
         typename HeadingType = defaultTypes::HeadingType,
         typename PathType = defaultTypes::PathType,
         typename GraphType = defaultTypes::GraphType>
class BFSDFS final : public PathPlanner<PoseType, HeadingType, PathType, GraphType> {
   public:
    BFSDFS()
    : PathPlanner<PoseType, HeadingType, PathType, GraphType>()
    , paths_()
    , leastTurnsPath_() {}

    auto update() -> void override final {
        buildDirectedGraph();
        searchPaths();
        searchLeastTurnsPath();
    }

    auto
    update(GraphType graph, PoseType destination, PoseType currentPose, HeadingType currentHeading)
        -> void {
        this->graph_ = graph;
        this->destination_ = destination;
        this->initialPose_ = currentPose;
        this->initialHeading_ = currentHeading;
        update();
    }

    auto update(PoseType destination, PoseType currentPose, HeadingType currentHeading) -> void {
        this->destination_ = destination;
        this->initialPose_ = currentPose;
        this->initialHeading_ = currentHeading;
        update();
    }

    auto update(GraphType graph) -> void {
        this->graph_ = graph;
        update();
    }

   private:
    auto print(std::ostream& os) const noexcept -> void {
        os << leastTurnsPath_->second << std::endl;
    }

    // Perform a BFS to get directedness of the graph from end_ to start_.
    auto buildDirectedGraph() -> void {
        this->graph_.at(this->destination_).first = 0;

        auto pathQueue = std::queue<std::pair<int, int>>();
        pathQueue.push(this->destination_);

        while (pathQueue.empty() == false) {
            auto const currentPosition = pathQueue.front();
            pathQueue.pop();

            // Found the destination.
            if (currentPosition == this->initialPose_) {
                break;
            }

            for (auto const& adjacentPosition : this->graph_.at(currentPosition).second) {
                // Give unvisited words a distance from source.
                if (this->graph_.at(adjacentPosition).first == unvisited) {
                    this->graph_.at(adjacentPosition).first =
                        this->graph_.at(currentPosition).first + 1;
                    pathQueue.push(adjacentPosition);
                }
            }
        }
    }

    // Perform a DFS to get the shortest possible paths from start_ to end_ and generate path plans
    // during DFS.
    auto searchPaths() -> void {
        auto path = std::vector<std::pair<int, int>>();
        path.emplace_back(this->initialPose_);

        auto pathStack = std::stack<std::tuple<std::pair<int, int>,
                                               std::vector<std::pair<int, int>>,
                                               std::string>>();  // [(point, path, pathPlan)]
        auto pathPlan = std::to_string(this->initialPose_.second)
                        + std::to_string(this->initialPose_.first)
                        + cardinalPoints[this->initialHeading_];
        pathStack.push({this->initialPose_, path, pathPlan});

        while (pathStack.empty() == false) {
            auto const [currentPosition, path, pathPlan] = pathStack.top();
            pathStack.pop();

            // Found the destination.
            if (currentPosition == this->destination_) {
                paths_.emplace_back(path, pathPlan);
            }

            for (auto const& adjacentPosition : this->graph_.at(currentPosition).second) {
                // Check for direction of graph.
                if (this->graph_.at(adjacentPosition).first
                    <= this->graph_.at(currentPosition).first) {
                    auto newPath = std::vector<std::pair<int, int>>(path);
                    newPath.emplace_back(adjacentPosition);

                    auto newPathPlan = pathPlan;
                    if (newPath.size() > 1) {
                        auto const& a = newPath.rbegin()[2];
                        auto const& b = newPath.rbegin()[1];
                        auto const& c = newPath.rbegin()[0];
                        if (newPath.size() > 2) {
                            newPathPlan += getAction(getHeadingIndex(a, b), getHeadingIndex(b, c));
                        }
                        else {
                            newPathPlan += getAction(this->initialHeading_, getHeadingIndex(b, c));
                        }
                    }
                    pathStack.push({adjacentPosition, newPath, newPathPlan});
                }
            }
        }
    }

    // Searches the shortest possible paths for any path with the least number of turns.
    auto searchLeastTurnsPath() noexcept -> void {
        auto checkTurn = [](auto const& c) { return c == 'L' || c == 'R'; };
        leastTurnsPath_ =
            std::min_element(paths_.begin(), paths_.end(), [checkTurn](auto const& a, auto const& b) {
                return std::count_if(a.second.begin(), a.second.end(), checkTurn)
                       < std::count_if(b.second.begin(), b.second.end(), checkTurn);
            });
        this->path_ = PathType(leastTurnsPath_->second.begin(), leastTurnsPath_->second.end());
    }

    // Gets the heading when moving from point a to point b.
    auto getHeadingIndex(std::pair<int, int> a, std::pair<int, int> b) const -> int {
        auto westEastHeading = a.first - b.first;  // W = 1, E = -1
        auto northSouthHeading = b.second - a.second;  // S = 1, N = -1
        auto heading = northSouthHeading == 0 ? westEastHeading + 2 : northSouthHeading + 1;
        return heading;
    }

    // Gets the required actions from heading a to heading b.
    auto getAction(int a, int b) const -> std::string {
        switch (a - b) {
        case 0: return "F";
        case -2:
        case 2: return "LLF";
        case -1:
        case 3: return "RF";
        case 1:
        case -3: return "LF";
        default: throw std::runtime_error("Invalid heading index.");
        }
    }

    // A vector of the shortest paths which is paired with their path plan sequence. Pythonically:
    // [(path, pathPlan)]
    std::vector<std::pair<std::vector<std::pair<int, int>>, std::string>> paths_;

    // An iterator to paths_ representing the shortest path with the least turns.
    std::vector<std::pair<std::vector<std::pair<int, int>>, std::string>>::iterator leastTurnsPath_;
};
}  // namespace mtrn4110
#endif  // BFS_DFS_HPP
