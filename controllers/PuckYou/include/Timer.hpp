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

    // Set a timer with the given duration.
    auto time(double duration) noexcept -> void;

    // Check if timer has expired.
    auto expired() const noexcept -> bool;

    // Blocking timer.
    auto wait(double duration) noexcept -> void;

    // Write timer to output stream.
    friend auto operator<<(std::ostream& os, Timer const& timer) noexcept -> std::ostream&;

   private:
    // To get access to Webots simulation time.
    webots::Robot const& robot_;

    // Reference time.
    double ref_;

    // Duration of timer.
    double exp_;
};

}  // namespace mtrn4110

#endif  // TIMER_HPP