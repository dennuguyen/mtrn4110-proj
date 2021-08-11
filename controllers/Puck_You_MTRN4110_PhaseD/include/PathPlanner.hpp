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

    // Automate any simple and periodic behaviours.
    virtual auto tick() -> void = 0;

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

   private:
    // Write any required data to an output stream.
    virtual auto print(std::ostream& os) const noexcept -> void = 0;

    GraphType graph_;
    PoseType destination_;
    PoseType currentPose_;
    HeadingType currentHeading_;
    MotionType motion_;
};
}  // namespace mtrn4110

#endif  // PATH_PLANNER_HPP