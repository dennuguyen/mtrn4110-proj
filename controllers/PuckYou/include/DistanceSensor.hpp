#ifndef DISTANCE_SENSOR_HPP
#define DISTANCE_SENSOR_HPP

#include <webots/DistanceSensor.hpp>
#include <webots/Robot.hpp>

#include <algorithm>
#include <memory>
#include <vector>

namespace mtrn4110 {
class DistanceSensor {
   public:
    DistanceSensor(webots::Robot& robot) {
        sensors_.resize(3);
        for (auto i = 0; i < 3; i++) {
            sensors_.emplace_back(robot.getDistanceSensor("ds" + std::to_string(i)),
                                  wallDistanceThreshold);
        }
    }

    auto updateDistance() noexcept -> void {
        std::for_each (sensors_.begin(), sensors_.end(), [](auto& sensor) {
            sensor.second = sensor.first->getValue();
        });
    }

    auto isLeftWall() const noexcept -> bool {
        return sensors_[2].second < wallDistanceThreshold;
    }

    auto isFrontWall() const noexcept -> bool {
        return sensors_[0].second < wallDistanceThreshold;
    }

    auto isRightWall() const noexcept -> bool {
        return sensors_[1].second < wallDistanceThreshold;
    }

    // Operator overload for <<.
    friend auto operator<<(std::ostream& os, DistanceSensor const& distanceSensor) noexcept
        -> std::ostream& {
        distanceSensor.print(os);
        return os;
    }

   private:
    auto print(std::ostream& os) const noexcept -> void {
        (void)os;
    }

    static auto constexpr wallDistanceThreshold = 575;
    std::vector<std::pair<std::unique_ptr<webots::DistanceSensor>, double>> sensors_;
};
}  // namespace mtrn4110

#endif  // DISTANCE_SENSOR_HPP