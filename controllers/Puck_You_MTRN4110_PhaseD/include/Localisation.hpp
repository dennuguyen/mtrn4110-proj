#ifndef LOCALISATION_HPP
#define LOCALISATION_HPP

#include <utility>

namespace mtrn4110 {

template <typename PoseType = std::pair<int, int>, typename HeadingType = double>
class Localisation {
   public:
    virtual ~Localisation() = 0;

    virtual auto getCurrentPose() const noexcept -> PoseType { return currentPose_; }
    virtual auto getCurrentHeading() const noexcept -> HeadingType { return currentHeading_; }

   private:
    PoseType currentPose_;
    HeadingType currentHeading_;
};
}  // namespace mtrn4110

#endif  // LOCALISATION_HPP