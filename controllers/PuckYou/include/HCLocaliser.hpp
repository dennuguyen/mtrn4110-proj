#ifndef HC_LOCALISER_HPP
#define HC_LOCALISER_HPP

#include "Localiser.hpp"

namespace mtrn4110 {
template<typename PoseType = defaultTypes::PoseType,
         typename HeadingType = defaultTypes::HeadingType,
         typename MotionType = defaultTypes::MotionType>
class HCLocaliser final : public Localiser<PoseType, HeadingType> {
   public:
    // Initialiser the localiser with an initial position and initial heading.
    HCLocaliser(PoseType initialPose, HeadingType initialHeading)
    : Localiser<PoseType, HeadingType, MotionType>(initialPose, initialHeading) {}

    // Update the position and heading of the robot by checking the given motion type and current
    // position and heading. It is up to the user that this function is called the right number of
    // times.
    auto updateLocale(MotionType motion) -> void {
        switch (motion) {
        case 'F': updatePosition(); break;
        case 'L':
            this->currentHeading_--;
            if (this->currentHeading_ < 0) {
                this->currentHeading_ += 4;
            }
            break;
        case 'R':
            this->currentHeading_++;
            if (this->currentHeading_ > 3) {
                this->currentHeading_ -= 4;
            }
            break;
        default: throw std::runtime_error("Invalid motion.");
        }
    }

   private:
    auto print(std::ostream& os) const noexcept -> void override final {
        (void)os;
    }

    // Update the position by checking the heading.
    auto updatePosition() -> void {
        switch (cardinalPoints[this->currentHeading_]) {
        case 'N': this->currentPose_.first--; break;
        case 'E': this->currentPose_.second++; break;
        case 'S': this->currentPose_.first++; break;
        case 'W': this->currentPose_.second--; break;
        default: throw std::runtime_error("Invalid character for cardinal direction.");
        }
    }
};
}  // namespace mtrn4110

#endif  // HC_LOCALISER_HPP