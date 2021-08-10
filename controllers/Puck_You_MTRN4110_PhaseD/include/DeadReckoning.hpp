#ifndef DEAD_RECKONING_HPP
#define DEAD_RECKONING_HPP

#include <utility>

#include "TrajectoryPlanner.hpp"

namespace mtrn4110 {

template<typename PoseType = double,
         typename VelocityType = double,
         typename MotionType = std::pair<PoseType, VelocityType>>
class DeadReckoning : public TrajectoryPlanner {
   public:
    DeadReckoning();
    DeadReckoning(const&) = delete;
    DeadReckoning(&&) = default;
    auto operator=(DeadReckoning const&) -> DeadReckoning& = delete;
    auto operator=(DeadReckoning&&) -> DeadReckoning& = default;
    ~DeadReckoning() override {}

    auto getNextMotion() const noexcept override final -> MotionType {
        return nextMotion_;
    }
    auto getPreviousMotion() const noexcept override final -> MotionType {
        return nextMotion_;
    }

   private:
    MotionType nextMotion_;
    MotionType previousMotion_;
};
}  // namespace mtrn4110

#endif  // DEAD_RECKONING_HPP