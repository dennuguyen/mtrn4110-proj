#ifndef TIMER_HPP
#define TIMER_HPP

#include <memory>
#include <ostream>
#include <webots/Robot.hpp>

namespace mtrn4110 {

class Timer {
   public:
    explicit Timer(webots::Robot const& robot);
    ~Timer() = default;

    auto time(double expiry) noexcept -> void;
    auto expired() const noexcept -> bool;
    friend auto operator<<(std::ostream& os, Timer const& timer) noexcept -> std::ostream&;

   private:
    webots::Robot const& robot_;
    double ref_;  // Time of reference
    double exp_;  // Expiry duration
};

}  // namespace mtrn4110

#endif  // TIMER_HPP