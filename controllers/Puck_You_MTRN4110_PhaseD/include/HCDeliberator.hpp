#ifndef HC_DELIBERATOR_HPP
#define HC_DELIBERATOR_HPP

#include "Deliberator.hpp"
#include "Util.hpp"

namespace mtrn4110 {

// A deliberator to operate the robot based on input motion commands from a file.
template<typename DeliberateType = std::vector<defaultTypes::MotionType>>
class HCDeliberator final : public Deliberator<DeliberateType>() {
   public:
    HCDeliberator()
    : Deliberator<DeliberateType>() {}

    // PUT PUBLIC METHODS HERE

   private:
    // PUT PRIVATE METHODS HERE

    // PUT PRIVATE MEMBERS HERE
};
}  // namespace mtrn4110

#endif  // HC_DELIBERATOR_HPP