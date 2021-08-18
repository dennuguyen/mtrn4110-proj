#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <memory>

#include <webots/Camera.hpp>
#include <webots/Robot.hpp>

namespace mtrn4110 {
class Camera {
   public:
    Camera(webots::Robot& robot)
    : camera_(robot.getCamera("camera")) {
        camera_->enable(robot.getBasicTimeStep());
    }

    // Take an image of the world from the robot's camera and save it to the outputFile.
    auto snap(std::string const& outputFile, int quality) const -> void {
        if (camera_->saveImage(outputFile, quality) != 0) {
            throw std::runtime_error("Could not save image to " + outputFile);
        }
    }

   private:
    std::unique_ptr<webots::Camera> camera_;
};
}  // namespace mtrn4110

#endif  // CAMERA_HPP