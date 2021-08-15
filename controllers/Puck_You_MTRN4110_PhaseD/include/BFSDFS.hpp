#ifndef BFS_DFS_HPP
#define BFS_DFS_HPP

#include "PathPlanner.hpp"

namespace mtrn4110 {

// Implementation of the path planner interface which uses a BFS + DFS algorithm to find shortest
// path.
template<typename PoseType = defaultTypes::PoseType,
         typename HeadingType = defaultTypes::HeadingType,
         typename MotionType = defaultTypes::MotionType,
         typename GraphType = defaultTypes::GraphType>
class BFSDFS final : public PathPlanner<PoseType, HeadingType, MotionType, GraphType> {
   public:
   private:
    // Perform a BFS on the graph to get directedness of the graph from end_ to start_.
    auto bfs() -> void {
        this->graph_.at(end_).first = 0;

        auto pathQueue = std::queue<std::pair<int, int>>();
        pathQueue.push(end_);

        while (pathQueue.empty() == false) {
            auto const currentPosition = pathQueue.front();
            pathQueue.pop();

            // Found the destination.
            if (currentPosition == start_) {
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

    // A vector of the shortest paths which is paired with their path plan sequence. Pythonically:
    // [(path, pathPlan)]
    std::vector<std::pair<std::vector<std::pair<int, int>>, std::string>> paths_;

    // An iterator to paths_ representing the shortest path with the least turns.
    std::vector<std::pair<std::vector<std::pair<int, int>>, std::string>>::iterator leastTurnsPath_;
};
}  // namespace mtrn4110
#endif  // BFS_DFS_HPP
