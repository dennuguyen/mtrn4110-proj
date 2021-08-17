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
        camera_->enable(robot.getTimeStep());
    }

    auto saveImage(std::string const& outputFile, int quality) const -> void {
        if (camera->saveImage(outputFile, quality) != 0) {
            throw std::runtime_error("Could not save image to " + outputFile);
        }
    }

   private:
    std::unique_ptr<webots::Camera> camera_;
};
}  // namespace mtrn4110

#endif  // CAMERA_HPP