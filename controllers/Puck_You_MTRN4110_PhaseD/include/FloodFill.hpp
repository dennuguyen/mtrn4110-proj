#ifndef FLOOD_FILL
#define FLOOD_FILL

#include "PathPlanner.hpp"
#include "Util.hpp"

namespace mtrn4110 {
// Implementation of path planner interface using flood filling.
template <
    typename PoseType = defaultType::PoseType, typename HeadingType = defaultType::HeadingType,
    typename MotionType = defaultType::MotionType, typename GraphType = defaultType::GraphType>
class FloodFill : public PathPlanner<PoseType, HeadingType, MotionType, GraphType> {
   public:
    FloodFill() {}  // EDIT CONSTRUCTOR PARAMETERS AS REQUIRED

    auto tick() -> void override final {}

    // ADD ANY PUBLIC METHODS BELOW HERE

   private:
    // ADD ANY PRIVATE MEMBERS BELOW HERE
};
}  // namespace mtrn4110

#endif  // FLOOD_FILL