#ifndef LOCALISER_HPP
#define LOCALISER_HPP

#include <utility>

#include "Util.hpp"

namespace mtrn4110 {

// An interface for a generic localiser.
template<typename PoseType = defaultType::PoseType, typename HeadingType = defaultType::HeadingType>
class Localiser {
   public:
    // Automate any simple and periodic behaviours.
    virtual auto tick() -> void = 0;

    auto getCurrentPose() const noexcept -> PoseType {
        return currentPose_;
    }
    auto getCurrentHeading() const noexcept -> HeadingType {
        return currentHeading_;
    }

    // Operator overload for <<.
    friend operator<<(std::ostream& os, PathPlanner const& pathPlanner) noexcept->std::ostream& {
        pathPlanner.print(os);
        return os;
    }

   private:
    // Write any required data to an output stream.
    virtual auto print(std::ostream& os) const noexcept -> void = 0;

    PoseType currentPose_;
    HeadingType currentHeading_;
};
} // namespace mtrn4110

#endif // LOCALISER_HPP