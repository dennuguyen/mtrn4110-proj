#ifndef FLOOD_FILL
#define FLOOD_FILL

#include "PathPlanner.hpp"
#include "Util.hpp"

namespace mtrn4110 {
// Implementation of path planner interface using flood filling.
template<typename PoseType = defaultTypes::PoseType,
         typename HeadingType = defaultTypes::HeadingType,
         typename MotionType = defaultTypes::MotionType,
         typename GraphType = defaultTypes::GraphType>
class FloodFill : public PathPlanner<PoseType, HeadingType, MotionType, GraphType> {
   public:
    FloodFill(GraphType graph, PoseType destination, PoseType initialPose, HeadingType initialHeading)
    : PathPlanner(graph, destination, initialPose, initialHeading) {}  // EDIT CONSTRUCTOR
                                                                       // PARAMETERS AS REQUIRED

    auto tick() -> void override final {}

    // ADD ANY PUBLIC METHODS BELOW HERE

   private:
    // ADD ANY PRIVATE METHODS BELOW HERE
    auto print(std::ostream& os) const noexcept -> void override final {}

    // ADD ANY PRIVATE MEMBERS BELOW HERE
};
}  // namespace mtrn4110

#endif  // FLOOD_FILL