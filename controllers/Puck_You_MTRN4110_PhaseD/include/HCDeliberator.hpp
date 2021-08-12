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

    auto readMotionPlanFile() -> void {
        // Read motion plan file.
        // print("Reading in motion plan from " + files::motionPlanPath + "...");
        auto motionPlanFile = std::fstream(files::motionPlanPath, std::fstream::in);
        if (motionPlanFile.good() == false) {
            throw std::runtime_error("Could not open file.");
        }

        // Get motion plan assuming it is valid.
        motionPlanFile >> this->delib_;
        // print("Motion Plan: " + motionPlan_);

        if (motionPlanFile.good() == false) {
            throw std::runtime_error("I/O error while reading.");
        }
        if (motionPlanFile.eof() == false) {
            throw std::runtime_error("Did not reach EOF.");
        }
        // print("Motion plan read in!");

        // print("Executing motion plan...");
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