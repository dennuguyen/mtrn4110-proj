#ifndef HC_PATH_PLANNER_HPP
#define HC_PATH_PLANNER_HPP

#include "PathPlanner.hpp"

namespace mtrn4110 {
// Class which takes in some path with valid motion types
template<typename PoseType = defaultTypes::PoseType,
         typename HeadingType = defaultTypes::HeadingType,
         typename MotionType = defaultTypes::MotionType,
         typename PathType = defaultTypes::PathType>
class PathSequencer {
   public:
    // Constructor for path sequencer to initialise the path.
    PathSequencer(DeliberateType motionSequence)
    : PathPlanner<PoseType, HeadingType, MotionType, GraphType>(graph,
                                                                destination,
                                                                initialPose,
                                                                initialHeading) {}

    auto computePath() -> void {}

   private:
    auto print(std::ostream& os) const noexcept -> void override final {
        (void)os;
    }
};
}  // namespace mtrn4110

#endif  // HC_PATH_PLANNER_HPP