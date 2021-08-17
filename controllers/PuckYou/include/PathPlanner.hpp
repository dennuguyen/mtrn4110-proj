#ifndef PATH_PLANNER_HPP
#define PATH_PLANNER_HPP

#include <map>
#include <vector>

#include "Util.hpp"

namespace mtrn4110 {

// An interface for a generic path planner.
template<typename PoseType = defaultTypes::PoseType,
         typename HeadingType = defaultTypes::HeadingType,
         typename PathType = defaultTypes::PathType,
         typename GraphType = defaultTypes::GraphType>
class PathPlanner {
   public:
    // Default constructor.
    PathPlanner() = default;

    // Constructor to initialise required members.
    PathPlanner(GraphType graph,
                PoseType destination,
                PoseType initialPose,
                HeadingType initialHeading,
                PathType path)
    : graph_(graph)
    , destination_(destination)
    , initialPose_(initialPose)
    , initialHeading_(initialHeading)
    , path_(path) {}

    auto getGraph() const noexcept -> GraphType {
        return graph_;
    }

    auto getDestination() const noexcept -> PoseType {
        return destination_;
    }

    auto getInitialPose() const noexcept -> PoseType {
        return initialPose_;
    }

    auto getInitialHeading() const noexcept -> HeadingType {
        return initialHeading_;
    }

    auto getPath() const noexcept -> PathType {
        return path_;
    }

    // Operator overload for <<.
    friend auto operator<<(std::ostream& os, PathPlanner const& pathPlanner) noexcept
        -> std::ostream& {
        pathPlanner.print(os);
        return os;
    }

   protected:
    GraphType graph_;
    PoseType destination_;
    PoseType initialPose_;
    HeadingType initialHeading_;
    PathType path_;

   private:
    // Update the path plan.
    virtual auto update() -> void = 0;

    // Write any required data to an output stream.
    virtual auto print(std::ostream& os) const noexcept -> void = 0;
};
}  // namespace mtrn4110

#endif  // PATH_PLANNER_HPP