#ifndef PATH_PLANNER_HPP
#define PATH_PLANNER_HPP

#include <map>
#include <vector>

#include "Util.hpp"

namespace mtrn4110 {

// An interface for a generic path planner.
template<typename PoseType = defaultTypes::PoseType,
         typename HeadingType = defaultTypes::HeadingType,
         typename MotionType = defaultTypes::MotionType,
         typename GraphType = defaultTypes::GraphType>
class PathPlanner {
   public:
    // Constructor to initialise required members.
    PathPlanner(GraphType graph, PoseType destination, PoseType initialPose, HeadingType initialHeading)
    : graph_(graph)
    , destination_(destination)
    , currentPose_(initialPose)
    , currentHeading_(initialHeading) {}

    auto getGraph() const noexcept -> GraphType {
        return graph_;
    }

    auto getDestination() const noexcept -> PoseType {
        return destination_;
    }

    auto getCurrentPose() const noexcept -> PoseType {
        return currentPose_;
    }

    auto getCurrentHeading() const noexcept -> HeadingType {
        return currentHeading_;
    }

    auto getMotion() const noexcept -> MotionType {
        return motion_;
    }

    // Operator overload for <<.
    friend auto operator<<(std::ostream& os, PathPlanner const& pathPlanner) noexcept
        -> std::ostream& {
        pathPlanner.print(os);
        return os;
    }

   protected:
    GraphType graph_;
    PoseType currentPose_;
    PoseType destination_;
    HeadingType currentHeading_;
    MotionType motion_;

   private:
    // Destination changes requires most current pose and current heading to update the path plan.
    virtual auto
    updateDestination(PoseType destination, PoseType currentPose, HeadingType currentHeading)
        -> void = 0;

    // World changes requires its graph representation, most current pose, and current heading to
    // update the path plan.
    virtual auto updateGraph(GraphType graph) -> void = 0;

    // Write any required data to an output stream.
    virtual auto print(std::ostream& os) const noexcept -> void = 0;
};
}  // namespace mtrn4110

#endif  // PATH_PLANNER_HPP