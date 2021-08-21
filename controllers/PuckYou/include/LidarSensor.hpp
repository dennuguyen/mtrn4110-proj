#ifndef PUCK_YOU_LIDAR_SENSOR_HPP
#define PUCK_YOU_LIDAR_SENSOR_HPP

#include <algorithm>
#include <cmath>
#include <memory>
#include <stdexcept>
#include <vector>

#include <webots/Lidar.hpp>
#include <webots/Robot.hpp>

#include "Timer.hpp"

namespace mtrn4110 {
class LidarSensor {
   public:
    LidarSensor(webots::Robot& robot)
    : lidar_(robot.getLidar("lidar")) {
        auto const timeStep = robot.getBasicTimeStep();
        lidar_->enable(timeStep);
        lidar_->enablePointCloud();

        auto timer = Timer(robot);
        timer.time(0.1);  // Give time for lidar to initialise.
    }

    // Use the lidar to detect nearby points that are within distance threshold.
    //
    // Distance threshold is in metres, any point distance below this is a nearby object.
    // Sector width is in degrees with a maximum of 360 degrees.
    // Point detection sensitivity within [0, 1].
    auto detectPoints(double const& distanceThreshold) const noexcept
        -> std::pair<std::vector<bool>, double> {
        auto pointCloud = lidar_->getPointCloud();
        while (pointCloud == nullptr) {
            pointCloud = lidar_->getPointCloud();
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

        // Convert point distances to a boolean if it is within obstacle distance.
        auto underThresholdPoints = std::vector<bool>();
        underThresholdPoints.reserve(numberPoints);
        for (auto const& point : pointDistances) {
            // This is preferred over std::transform as order is important.
            underThresholdPoints.push_back(point < distanceThreshold);
        }

        auto const pointDensity = static_cast<double>(numberPoints / lidarAngle_);
        return {underThresholdPoints, pointDensity};
    }

    // Detects points within a sector width of a cardinal direction (with respect to the robot).
    // Cardinality order is left, front, right, back.
    auto detectCardinal(double const& distanceThreshold,
                        double const& sectorWidth,
                        double const& sensitivity) const noexcept -> std::vector<int> {
        auto const [points, pointDensity] = detectPoints(distanceThreshold);

        // Convert sector angles into point densities.
        auto const startAngle = static_cast<double>(90.0 - 0.75 * sectorWidth);
        auto const pointStart = static_cast<int>(pointDensity * startAngle);
        auto pointSpread = static_cast<int>(pointDensity * sectorWidth);
        auto pointOnset = pointStart;

        // Get number of distances for a section that is within object distance.
        auto const pointThreshold = static_cast<int>(pointDensity * sensitivity);
        auto nearbyObjects = std::vector<int>(4);
        for (auto& object : nearbyObjects) {
            // Count how many under threshold points are above point threshold.
            object = std::count(points.begin() + pointOnset,
                                points.begin() + pointOnset + pointSpread,
                                true)
                             > pointThreshold
                         ? true
                         : false;
            // Check the next cardinal sector.
            pointOnset += (pointStart + pointSpread);
        }

        return nearbyObjects;
    }

    // Detects any obstacle within the lidar range. It is recommended this function only to be used
    // for extremely short distances.
    auto detectAny(double const& distanceThreshold,
                   double const& sectorWidth,
                   double const& sensitivity) const noexcept -> bool {
        auto const nearbyObjects = detectCardinal(distanceThreshold, sectorWidth, sensitivity);
        return std::any_of(nearbyObjects.begin(), nearbyObjects.end(), [](auto const& i) {
            return i == true;
        });
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

    static auto constexpr lidarAngle_ = 360.0;
    std::unique_ptr<webots::Lidar> lidar_;
};
}  // namespace mtrn4110

#endif  // PUCK_YOU_DISTANCE_SENSOR_HPP