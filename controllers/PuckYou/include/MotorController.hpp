#ifndef PUCK_YOU_MOTOR_CONTROLLER_HPP
#define PUCK_YOU_MOTOR_CONTROLLER_HPP

#include <cmath>
#include <memory>
#include <tuple>

#include <webots/Motor.hpp>
#include <webots/PositionSensor.hpp>
#include <webots/Robot.hpp>

namespace mtrn4110 {
class MotorController {
   public:
    MotorController(webots::Robot& robot)
    : leftMotor_(robot.getMotor("left wheel motor"))
    , rightMotor_(robot.getMotor("right wheel motor"))
    , leftPositionSensor_(robot.getPositionSensor("left wheel sensor"))
    , rightPositionSensor_(robot.getPositionSensor("right wheel sensor")) {
        // Initialise position sensors.
        auto const timeStep = robot.getBasicTimeStep();
        leftPositionSensor_->enable(timeStep);
        rightPositionSensor_->enable(timeStep);

        // Initialise motors.
        setGain({9.58, 0, 0.78}, {9.58, 0, 0.78});
        setPosition(0, 0);
        setVelocity(0, 0);
    }

    auto isAtPosition() const noexcept -> bool {
        auto const diffLeft = leftMotor_->getTargetPosition() - leftPositionSensor_->getValue();
        auto const diffRight = rightMotor_->getTargetPosition() - rightPositionSensor_->getValue();
        return diffLeft < atPositionSensitivity && diffRight < atPositionSensitivity;
    }

    auto getMotorPositions() const noexcept -> std::pair<double, double> {
        return {leftPositionSensor_->getValue(), rightPositionSensor_->getValue()};
    }

    auto setGain(std::tuple<double, double, double> const leftMotorPID,
                 std::tuple<double, double, double> const rightMotorPID) noexcept -> void {
        leftMotor_->setControlPID(std::get<0>(leftMotorPID),
                                  std::get<1>(leftMotorPID),
                                  std::get<2>(leftMotorPID));
        rightMotor_->setControlPID(std::get<0>(rightMotorPID),
                                   std::get<1>(rightMotorPID),
                                   std::get<2>(rightMotorPID));
    }

    auto setPosition(std::pair<double, double> const& motorPositions) noexcept -> void {
        setPosition(motorPositions.first, motorPositions.second);
    }

    auto setPosition(double const& leftMotorPosition, double const& rightMotorPosition) noexcept
        -> void {
        auto const leftInitial = leftPositionSensor_->getValue();
        auto const rightInitial = rightPositionSensor_->getValue();
        leftMotor_->setPosition(leftInitial + leftMotorPosition);
        rightMotor_->setPosition(rightInitial + rightMotorPosition);
    }

    auto setVelocity(std::pair<double, double> const& motorVelocities) noexcept -> void {
        setVelocity(motorVelocities.first, motorVelocities.second);
    }

    auto setVelocity(double const& leftMotorVelocity, double const& rightMotorVelocity) noexcept
        -> void {
        leftMotor_->setVelocity(std::abs(leftMotorVelocity));
        rightMotor_->setVelocity(std::abs(rightMotorVelocity));
    }

   private:
    static auto constexpr atPositionSensitivity = 0.0005;
    std::unique_ptr<webots::Motor> leftMotor_;
    std::unique_ptr<webots::Motor> rightMotor_;
    std::unique_ptr<webots::PositionSensor> leftPositionSensor_;
    std::unique_ptr<webots::PositionSensor> rightPositionSensor_;
};
}  // namespace mtrn4110

#endif  // PUCK_YOU_MOTOR_CONTROLLER_HPP