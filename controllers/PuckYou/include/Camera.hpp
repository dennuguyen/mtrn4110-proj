#ifndef PUCK_YOU_CAMERA_HPP
#define PUCK_YOU_CAMERA_HPP

#include <memory>

#include <webots/Camera.hpp>
#include <webots/Robot.hpp>

namespace mtrn4110 {
class Camera {
   public:
    Camera(webots::Robot& robot)
    : timeStep_(robot.getBasicTimeStep())
    , camera_(robot.getCamera("bird")) {
        camera_->enable(timeStep_);
    }

    // Take an image of the world from the robot's camera and save it to the outputFile. Camera is
    // only enabled when used.
    auto snap(std::string const& outputFile, int quality) const -> void {
        try {
            if (camera_->saveImage(outputFile, quality) != 0) {
                throw std::runtime_error("Could not save image to " + outputFile);
            }
        } catch (std::runtime_error const& e) {
            // Try saving the image one more time.
            if (camera_->saveImage(outputFile, quality) != 0) {
                throw e;
            }
        }
    }

   private:
    int const timeStep_;
    std::unique_ptr<webots::Camera> camera_;
};
}  // namespace mtrn4110

#endif  // PUCK_YOU_CAMERA_HPP