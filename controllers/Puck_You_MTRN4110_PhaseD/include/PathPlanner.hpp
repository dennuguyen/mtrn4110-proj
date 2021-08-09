#ifndef PATH_PLANNER_HPP
#define PATH_PLANNER_HPP

#include <map>
#include <vector>

namespace mtrn4110 {

template <typename PoseType = defaultType::PoseType,
          typename HeadingType = defaultType::HeadingType,
          typename MotionType = defaultType::MotionType,
          typename GraphType = defaultType::GraphType>
class PathPlanner {
   public:
    // Constructor to initialise required members.
    PathPlanner(GraphType graph, PoseType destination, PoseType initialPose,
                HeadingType initialHeading, MotionType motion)
        : graph_(graph),
          destination_(destination),
          currentPose_(initialPose),
          currentHeading_(initialHeading),
          motion_(motion) {}

    // Enforce derived classes to implement this method.
    virtual auto tick() -> void = 0;

    auto getGraph() const noexcept -> GraphType { return graph_; }
    auto getDestination() const noexcept -> PoseType { return destination_; }
    auto getCurrentPose() const noexcept -> PoseType { return currentPose_; }
    auto getCurrentHeading() const noexcept -> HeadingType { return currentHeading_; }
    auto getMotion() const noexcept -> MotionType { return motion_; }

   private:
    GraphType graph_;
    PoseType destination_;
    PoseType currentPose_;
    HeadingType currentHeading_;
    MotionType motion_;
};
}  // namespace mtrn4110

#endif  // PATH_PLANNER_HPP