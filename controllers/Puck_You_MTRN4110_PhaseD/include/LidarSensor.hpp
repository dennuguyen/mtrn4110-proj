#ifndef LIDAR_SENSOR_HPP
#define LIDAR_SENSOR_HPP

#include <webots/Lidar.hpp>
#include <webots/Robot.hpp>

#include <algorithm>
#include <cmath>
#include <memory>
#include <vector>

namespace mtrn4110 {
class LidarSensor {
   public:
    LidarSensor(webots::Robot& robot)
    : lidar_(robot.getLidar("lidar")) {
        auto const timeStep = robot.getBasicTimeStep();
        lidar_->enable(timeStep);
        lidar_->enablePointCloud();

        // Let LIDAR initialise because poor simulation design.
        while (updateLidar() == -1) {
            robot.step(timeStep);
        }
    }

    auto updateLidar() noexcept -> int {
        auto const pointCloud = lidar_->getPointCloud();
        if (pointCloud == nullptr) {
            return -1;
        }

        // Convert (x, y) into distances.
        auto const numberPoints = lidar_->getNumberOfPoints();
        auto pointDistances = std::vector<double>();
        pointDistances.reserve(numberPoints);

        // This is preferred over std::transform as order is important.
        for (int i = 0; i < numberPoints; i++) {
            pointDistances.emplace_back(
                std::sqrt(std::pow(pointCloud[i].x, 2) + std::pow(pointCloud[i].z, 2)));
        }

        // Convert point distances to a boolean if it is within wall distance
        // range.
        auto wallDetected = std::vector<bool>();
        wallDetected.reserve(numberPoints);

        // This is preferred over std::transform as order is important.
        for (auto const& point : pointDistances) {
            wallDetected.push_back(point < wallDistance);
        }

        // Convert sector angles into point densities.
        auto const pointDensity = static_cast<double>(numberPoints / 360.0);
        auto const pointStart = static_cast<int>(pointDensity * startAngle);
        auto pointSpread = static_cast<int>(pointDensity * sectorWidth);
        auto pointOnset = pointStart;

        // Get number of distances for a section that is within wall distance.
        auto const pointThreshold = static_cast<int>(pointDensity * sensitivity);
        for (auto& wall : walls_) {
            wall = std::count(wallDetected.begin() + pointOnset,
                              wallDetected.begin() + pointOnset + pointSpread,
                              true)
                           > pointThreshold
                       ? 'Y'
                       : 'N';
            pointOnset += (pointStart + pointSpread);
        }

        return 0;
    }

    auto isLeftWall() const noexcept -> bool {
        return walls_[0];
    }

    auto isFrontWall() const noexcept -> bool {
        return walls_[1];
    }

    auto isRightWall() const noexcept -> bool {
        return walls_[2];
    }

    // Operator overload for <<.
    friend auto operator<<(std::ostream& os, LidarSensor const& lidarSensor) noexcept
        -> std::ostream& {
        lidarSensor.print(os);
        return os;
    }

   private:
    auto print(std::ostream& os) const noexcept -> void {
        (void)os;
    }

    static constexpr auto wallDistance = 0.085;  // Distance from centre of cell to wall.
    static constexpr auto sectorWidth = 20.0;  // Width of sector in degrees.
    static constexpr auto startAngle = static_cast<double>(90.0 - 0.75 * sectorWidth);
    static constexpr auto sensitivity = 0.9;  // Point detection sensitivity within [0, 1]

    std::unique_ptr<webots::Lidar> lidar_;  // 360 lidar.
    std::array<char, 3> walls_;
};
}  // namespace mtrn4110

#endif  // DISTANCE_SENSOR_HPP