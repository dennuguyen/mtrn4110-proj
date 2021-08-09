#include "Timer.hpp"

namespace mtrn4110 {

Timer::Timer(webots::Robot const& robot) : robot_(robot), ref_(), exp_() {}

auto Timer::time(double expiry) noexcept -> void {
    ref_ = robot_.getTime();
    exp_ = expiry;
}

auto const Timer::expired() const noexcept -> bool { return (robot_.getTime() - ref_) > exp_; }

auto operator<<(std::ostream& os, Timer const& timer) noexcept -> std::ostream& {
    os << "Time: " << timer.ref_ << std::endl;
    os << "Expiry: " << timer.exp_ << std::endl;
    return os;
}

}  // namespace mtrn4110