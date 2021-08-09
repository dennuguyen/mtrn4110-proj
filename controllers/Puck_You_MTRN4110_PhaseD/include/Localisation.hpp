#ifndef LOCALISATION_HPP
#define LOCALISATION_HPP

#include <utility>

namespace mtrn4110 {

template <typename PoseType = defaultType::PoseType,
          typename HeadingType = defaultType::HeadingType>
class Localisation {
   public:
    // Constructor to initialise required members.
    Localisation(PoseType initialPose, HeadingType initialHeading)
        : currentPose_(initialPose), currentHeading_(initialHeading) {}

    // Enforce derived classes to implement this method.
    virtual ~Localisation() = 0;

    auto getCurrentPose() const noexcept -> PoseType { return currentPose_; }
    auto getCurrentHeading() const noexcept -> HeadingType { return currentHeading_; }

   private:
    PoseType currentPose_;
    HeadingType currentHeading_;
};
}  // namespace mtrn4110

#endif  // LOCALISATION_HPP