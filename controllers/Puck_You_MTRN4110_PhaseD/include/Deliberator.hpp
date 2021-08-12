#ifndef DELIBERATOR_HPP
#define DELIBERATOR_HPP

#include <utility>

#include "Util.hpp"

namespace mtrn4110 {

// An interface for a generic waypoint deliberator.
template<typename DeliberateType = defaultTypes::MotionType>
class Deliberator {
   public:
    // Constructor to initialise deliberation type.
    Deliberator()
    : delib_() {}

    auto getDeliberatedValue() const noexcept -> DeliberateType {
        return delib_;
    }

    // Operator overload for <<.
    friend auto operator<<(std::ostream& os, Deliberator const& deliberator) noexcept
        -> std::ostream& {
        deliberator.print(os);
        return os;
    }

   protected:
    DeliberateType delib_;  // This is the variable we want to output.

   private:
    // Write any required data to an output stream.
    virtual auto print(std::ostream& os) const noexcept -> void = 0;
};
}  // namespace mtrn4110

#endif  // DELIBERATOR_HPP