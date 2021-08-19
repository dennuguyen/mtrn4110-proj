#ifndef PUCK_YOU_CAMERA_HPP
#define PUCK_YOU_CAMERA_HPP

#include <memory>

#include <webots/Camera.hpp>
#include <webots/Robot.hpp>

namespace mtrn4110 {
class Camera {
   public:
    Camera(webots::Robot& robot)
    : camera_(robot.getCamera("bird"), timeStep_(robot.getBasicTimeStep())) {}

    // Take an image of the world from the robot's camera and save it to the outputFile. Camera is
    // only enabled when used.
    auto snap(std::string const& outputFile, int quality) const -> void {
        camera_->enable(timeStep_);
        if (camera_->saveImage(outputFile, quality) != 0) {
            throw std::runtime_error("Could not save image to " + outputFile);
        }
        camera_->disable();
    }

   private:
    std::unique_ptr<webots::Camera> camera_;
    auto const timeStep_;
};
}  // namespace mtrn4110

#endif  // PUCK_YOU_CAMERA_HPP