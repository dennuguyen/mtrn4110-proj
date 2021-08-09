#ifndef EPUCK_MODEL_HPP
#define EPUCK_MODEL_HPP

#include "KinematicModel.hpp"

namespace mtrn4110 {
class EPuckModel : public KinematicModel {
   public:
    static constexpr double wheelRadius = 0.02;
    static constexpr double axleLength = 0.0566;
    static constexpr double maxMotorSpeed = 6.28;

   private:
};
}  // namespace mtrn4110

#endif  // EPUCK_MODEL_HPP