#ifndef WAYPOINT_DELIBERATOR_HPP
#define WAYPOINT_DELIBERATOR_HPP

#include <utility>

namespace mtrn4110 {

// An interface for a generic waypoint deliberator.
template<typename PoseType = defaultTypes::PoseType>
class WaypointDeliberator {
   public:
    // Automate any simple and periodic behaviours.
    virtual auto tick() -> void = 0;

    auto getDestination() const noexcept -> PoseType {
        return destination_;
    }

    // Operator overload for <<.
    friend auto operator<<(std::ostream& os, WaypointDeliberator const& waypointDeliberator) noexcept
        -> std::ostream& {
        waypointDeliberator.print(os);
        return os;
    }

   private:
    // Write any required data to an output stream.
    virtual auto print(std::ostream& os) const noexcept -> void = 0;

    PoseType destination_;
};
}  // namespace mtrn4110

#endif  // WAYPOINT_DELIBERATOR_HPP