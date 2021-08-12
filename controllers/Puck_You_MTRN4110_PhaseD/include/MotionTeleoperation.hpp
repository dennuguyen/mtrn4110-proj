#ifndef MOTION_TELEOPERATION_HPP
#define MOTION_TELEOPERATION_HPP

#include "Deliberator.hpp"
#include "Util.hpp"

namespace mtrn4110 {

// A deliberator to teleoperate the robot based on input motion commands. The input may be a
// character or string of motions.
template<typename DeliberateType = defaultTypes::MotionType>
class MotionTeleoperation final : public Deliberator<DeliberateType>() {
   public:
    MotionTeleoperation()
    : Deliberator<DeliberateType>() {}

    // PUT PUBLIC METHODS HERE

   private:
    // PUT PRIVATE METHODS HERE

    // PUT PRIVATE MEMBERS HERE
};
}  // namespace mtrn4110

#endif  // MOTION_TELEOPERATION_HPP