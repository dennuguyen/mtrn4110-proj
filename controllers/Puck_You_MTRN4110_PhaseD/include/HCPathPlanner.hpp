#ifndef HC_PATH_PLANNER_HPP
#define HC_PATH_PLANNER_HPP

#include "PathPlanner.hpp"

namespace mtrn4110 {
template<typename PoseType = defaultTypes::PoseType,
         typename HeadingType = defaultTypes::HeadingType,
         typename MotionType = defaultTypes::MotionType,
         typename GraphType = std::string>
class HCPathPlanner final : public PathPlanner<PoseType, HeadingType, MotionType, GraphType> {
   public:
    // Constructor for hard-coded path planner to initialise graph, destination, initial pose, and
    // initial heading.
    HCPathPlanner(GraphType graph, PoseType destination, PoseType initialPose, HeadingType initialHeading)
    : PathPlanner<PoseType, HeadingType, MotionType, GraphType>(graph,
                                                                destination,
                                                                initialPose,
                                                                initialHeading) {}

    auto computePath() -> void {}

   private:
    auto print(std::ostream& os) const noexcept -> void {
        (void)os;
    }
};
}  // namespace mtrn4110

#endif  // HC_PATH_PLANNER_HPP