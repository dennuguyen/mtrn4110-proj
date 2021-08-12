#ifndef HC_LOCALISER_HPP
#define HC_LOCALISER_HPP

#include "Localiser.hpp"

namespace mtrn4110 {
template<typename PoseType = defaultTypes::PoseType, typename HeadingType = defaultTypes::HeadingType>
class HCLocaliser final : public Localiser<PoseType, HeadingType> {
   public:
    // Initialiser the localiser with an initial position and initial heading.
    HCLocaliser(PoseType initialPose, HeadingType initialHeading)
    : Localiser<PoseType, HeadingType>(initialPose, initialHeading) {}

    // Update the position and heading of the robot by checking the given motion type and current
    // position and heading. It is up to the user that this function is called the right number of
    // times.
    auto updateLocale(MotionType motion) -> void override final {
        switch (motion) {
        case 'F': updatePosition(); break;
        case 'L':
            headingIndex_--;
            if (headingIndex_ < 0) {
                headingIndex_ += 4;
            }
            break;
        case 'R':
            headingIndex_++;
            if (headingIndex_ > 3) {
                headingIndex_ -= 4;
            }
            break;
        default: throw std::runtime_error("Invalid motion.");
        }
    }

   private:
    auto print(std::ostream& os) const noexcept -> void override final {}

    // Update the position by checking the heading.
    auto updatePosition() -> void {
        switch (getHeading()) {
        case 'N': position_.first--; break;
        case 'E': position_.second++; break;
        case 'S': position_.first++; break;
        case 'W': position_.second--; break;
        default: throw std::runtime_error("Invalid character for cardinal direction.");
        }
    }
};
}  // namespace mtrn4110

#endif  // HC_LOCALISER_HPP