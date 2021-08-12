#ifndef MOTION_TELEOPERATION_HPP
#define MOTION_TELEOPERATION_HPP

#include <memory>
#include <webots/Keyboard.hpp>
#include <webots/Webots.hpp>

#include "Deliberator.hpp"
#include "Util.hpp"

namespace mtrn4110 {

// A deliberator to teleoperate the robot based on input motion commands. The input may be a
// character or string of motions.
template<typename DeliberateType = std::vector<defaultTypes::MotionType>>
class MotionTeleoperation final : public Deliberator<DeliberateType>() {
   public:
    MotionTeleoperation(webots::Webots& robot)
    : Deliberator<DeliberateType>()
    , keyboard_(robot.getKeyboard()) {
        // INITIALISE OTHER STUFF HERE
    }

    // PUT PUBLIC METHODS HERE

   private:
    // PUT PRIVATE METHODS HERE
    auto print(std::ostream& os) const noexcept -> void {
        (void)os;
    }

    // PUT PRIVATE MEMBERS HERE
    std::unique_ptr<webots::Keyboard> keyboard_;
};
}  // namespace mtrn4110

#endif  // MOTION_TELEOPERATION_HPP