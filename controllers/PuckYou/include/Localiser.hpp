#ifndef LOCALISER_HPP
#define LOCALISER_HPP

#include <utility>

#include "Util.hpp"

namespace mtrn4110 {

// An interface for a generic localiser.
template<typename PoseType = defaultTypes::PoseType,
         typename HeadingType = defaultTypes::HeadingType,
         typename MotionType = defaultTypes::MotionType>
class Localiser {
   public:
    // Default constructor.
    Localiser() = default;

    // Constructor taking an initial pose and initial heading.
    Localiser(PoseType initialPose, HeadingType initialHeading)
    : currentPose_(initialPose)
    , currentHeading_(initialHeading) {}

    auto getCurrentPose() const noexcept -> PoseType {
        return currentPose_;
    }

    auto getCurrentHeading() const noexcept -> HeadingType {
        return currentHeading_;
    }

    // Operator overload for <<.
    friend auto operator<<(std::ostream& os, Localiser const& localiser) noexcept -> std::ostream& {
        localiser.print(os);
        return os;
    }

   protected:
    PoseType currentPose_;
    HeadingType currentHeading_;

   private:
    // Write any required data to an output stream.
    virtual auto print(std::ostream& os) const noexcept -> void = 0;
};
}  // namespace mtrn4110

#endif  // LOCALISER_HPP