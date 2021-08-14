#ifndef HC_DELIBERATOR_HPP
#define HC_DELIBERATOR_HPP

#include <fstream>
#include <stdexcept>
#include <vector>

#include "Deliberator.hpp"
#include "Util.hpp"

namespace mtrn4110 {

// A deliberator to operate the robot based on input motion commands from a file.
template<typename PoseType = defaultTypes::PoseType,
         typename HeadingType = defaultTypes::HeadingType,
         typename DeliberateType = defaultTypes::PathType>
class HCDeliberator final : public Deliberator<DeliberateType> {
   public:
    HCDeliberator()
    : Deliberator<DeliberateType>() {}

    auto readInput(std::istream& inputStream) -> void override final {
        // Read motion plan file.
        if (inputStream.good() == false) {
            throw std::runtime_error("Could not open file.");
        }

        // Get motion plan assuming it is valid.
        inputStream >> this->delib_;

        if (inputStream.good() == false) {
            throw std::runtime_error("I/O error while reading.");
        }
        if (inputStream.eof() == false) {
            throw std::runtime_error("Did not reach EOF.");
        }
    }

    auto getInitialLocale() const noexcept -> std::pair<PoseType, HeadingType> {
        // auto const pose = std::make_pair<PoseType>(static_cast<int>(delib_[0]),
        // static_cast<int>(delib_[1]));
        return {{this->delib_[0], this->delib_[1]}, this->delib_[2]};
    }

   private:
    auto print(std::ostream& os) const noexcept -> void {
        (void)os;
    }
};
}  // namespace mtrn4110

#endif  // HC_DELIBERATOR_HPP