#ifndef LOCALISER_HPP
#define LOCALISER_HPP

#include <utility>

namespace mtrn4110 {

// An interface for a generic localiser.
template <typename PoseType = defaultType::PoseType,
          typename HeadingType = defaultType::HeadingType>
class Localiser {
   public:
    // Constructor to initialise required members.
    Localiser(PoseType initialPose, HeadingType initialHeading)
        : currentPose_(initialPose), currentHeading_(initialHeading) {}

    // Enforce derived classes to implement this method.
    virtual ~Localiser() = 0;

    auto getCurrentPose() const noexcept -> PoseType { return currentPose_; }
    auto getCurrentHeading() const noexcept -> HeadingType { return currentHeading_; }

   private:
    PoseType currentPose_;
    HeadingType currentHeading_;
};
}  // namespace mtrn4110

#endif  // LOCALISER_HPP