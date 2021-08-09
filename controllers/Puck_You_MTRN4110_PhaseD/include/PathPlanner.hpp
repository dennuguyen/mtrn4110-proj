#ifndef PATH_PLANNER_HPP
#define PATH_PLANNER_HPP

#include <map>
#include <vector>

namespace mtrn4110 {

template <typename PoseType = std::pair<int, int>, typename HeadingType = int,
          typename MotionType = std::pair<double, double>,
          typename GraphType = std::map<PoseType, std::pair<int, std::vector<PoseType>>>>
class PathPlanner {
   public:
    virtual ~PathPlanner() = 0;

    virtual auto getGraph() const noexcept -> GraphType { return graph_; }
    virtual auto getDestination() const noexcept -> PoseType { return destination_; }
    virtual auto getCurrentPose() const noexcept -> PoseType { return currentPose_; }
    virtual auto getCurrentHeading() const noexcept -> HeadingType { return currentHeading_; }
    virtual auto getMotion() const noexcept -> MotionType { return motion_; }

   private:
    GraphType graph_;
    PoseType destination_;
    PoseType currentPose_;
    HeadingType currentHeading_;
    MotionType motion_;
};
}  // namespace mtrn4110

#endif  // PATH_PLANNER_HPP