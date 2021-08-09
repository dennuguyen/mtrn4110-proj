#ifndef WAYPOINT_DELIBERATOR_HPP
#define WAYPOINT_DELIBERATOR_HPP

#include <utility>

namespace mtrn4110 {

template <typename PoseType = std::pair<int, int>>
class WaypointDeliberator {
   public:
    virtual ~WaypointDeliberator() = 0;

    virtual auto getDestination() const noexcept -> PoseType { return destination_; }

   private:
    PoseType destination_;
};
}  // namespace mtrn4110

#endif  // WAYPOINT_DELIBERATOR_HPP