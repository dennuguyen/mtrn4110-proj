#ifndef WAYPOINT_DELIBERATOR_HPP
#define WAYPOINT_DELIBERATOR_HPP

#include <utility>

namespace mtrn4110 {

// An interface for a generic waypoint deliberator.
template <typename PoseType = defaultType::PoseType>
class WaypointDeliberator {
   public:
    // Constructor to initialise required members.
    WaypointDeliberator(PoseType destination) : destination_(destination) {}

    // Enforce derived classes to implement this method.
    virtual auto tick() -> void = 0;

    auto getDestination() const noexcept -> PoseType { return destination_; }

   private:
    PoseType destination_;
};
}  // namespace mtrn4110

#endif  // WAYPOINT_DELIBERATOR_HPP