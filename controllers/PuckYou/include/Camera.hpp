#ifndef PUCK_YOU_CAMERA_HPP
#define PUCK_YOU_CAMERA_HPP

#include <memory>

#include <webots/Camera.hpp>
#include <webots/Robot.hpp>

namespace mtrn4110 {
class Camera {
   public:
    Camera(webots::Robot& robot)
    : robot_(robot)
    , camera_(robot.getCamera("bird")) {}

    // Take an image of the world from the robot's camera and save it to the outputFile. Camera is
    // only enabled when used.
    auto snap(std::string const& outputFile, int quality) const -> void {
        camera_->enable(robot.getBasicTimeStep());
        robot_.step(robot.getBasicTimeStep());
        if (camera_->saveImage(outputFile, quality) != 0) {
            throw std::runtime_error("Could not save image to " + outputFile);
        }
        camera_->disable();
    }

   private:
    webots::Robot const& robot_;
    std::unique_ptr<webots::Camera> camera_;
};
}  // namespace mtrn4110

#endif  // PUCK_YOU_CAMERA_HPP