#ifndef SIMPLE_TELEOPERATION_HPP
#define SIMPLE_TELEOPERATION_HPP

#include <memory>
#include <vector>

#include <webots/Keyboard.hpp>
#include <webots/Robot.hpp>

#include "Deliberator.hpp"
#include "Util.hpp"

namespace mtrn4110 {

// A deliberator to teleoperate the robot based on input motion commands. Teleoperation is based on
// WQE which corresponds to FLR. The Webots keyboard is non-blocking.
template<typename DeliberateType = char>
class SimpleTeleoperation final : public Deliberator<DeliberateType> {
   public:
    SimpleTeleoperation(webots::Robot& robot)
    : Deliberator<DeliberateType>()
    , keyboard_(robot.getKeyboard()) {
        keyboard_->enable(robot.getBasicTimeStep());
    }

    auto readInput() -> void {
        switch (keyboard_->getKey()) {
        case 'W': this->delib_ = 'F'; break;
        case 'Q': this->delib_ = 'L'; break;
        case 'E': this->delib_ = 'R'; break;
        default: this->delib_ = '\0'; break;
        }
    }

   private:
    auto print(std::ostream& os) const noexcept -> void {
        os << this->delib_ << std::endl;
    }

    std::unique_ptr<webots::Keyboard> keyboard_;
};
}  // namespace mtrn4110

#endif  // SIMPLE_TELEOPERATION_HPP
