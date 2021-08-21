#include <Python.h>

#include <iostream>
#include <thread>

#include <webots/Robot.hpp>

// Used in both teleoperation and autonomous control.
#include "DeadReckoning.hpp"
#include "EPuckMotionPlanner.hpp"
#include "LidarSensor.hpp"
#include "MotorController.hpp"
#include "SimpleTeleoperation.hpp"

// Extra control over control loop.
#include "TaskControl.hpp"

// Perform simulation steps until Webots is stopping the controller.
static auto simulationSteps(webots::Robot& robot) -> void {
    auto const timeStep = robot.getBasicTimeStep();
    while (robot.step(timeStep) != -1) {
    }
}

// Perform real-time steps.
// This function contains the control loop logic for the EPuck. It supports only teleoperation.
static auto realTimeSteps(webots::Robot& robot) -> void {
    // Instantiate our task controller class.
    auto taskControl = mtrn4110::TaskControl(robot, 1, 1);
    auto constexpr motionLock = 0;  // true = in motion, false = not in motion
    auto constexpr motionTimer = 0;  // true = in motion, false = not in motion

    // These RSA elements are used in both teleoperation and autonomous control.
    auto teleoperation = mtrn4110::SimpleTeleoperation(robot);
    auto trajectoryPlanner = mtrn4110::DeadReckoning('\0');
    auto motionPlanner = mtrn4110::EPuckMotionPlanner();
    auto motorController = mtrn4110::MotorController(robot);
    auto lidarSensor = mtrn4110::LidarSensor(robot);

    // Enter control loop.
    while (1) {
        auto motion = '\0';

        // Get teleoperation motion command.
        auto const key = teleoperation.readInput();
        motion = teleoperation.getDeliberatedValue();

        // Don't drive into obstacles.
        if (lidarSensor.detectCardinal(mtrn4110::models::maze.distanceBetweenCells / 2, 20, 0.9)[1]
                == true
            && motion == 'F') {
            continue;
        }

        // Calculate the trajectory.
        trajectoryPlanner.updateMotion(motion);
        trajectoryPlanner.computeTrajectory({0.008, 0, 0}, {0, 0, 0.04});

        // Calculate the motor setpoints for current trajectory.
        auto const angle = trajectoryPlanner.getAngle();
        auto const distance = trajectoryPlanner.getDistance();
        auto const linearVelocity = trajectoryPlanner.getLinearVelocity();
        auto const angularVelocity = trajectoryPlanner.getAngularVelocity();
        motionPlanner.computeMotorSetpoints(angle, distance, linearVelocity, angularVelocity);

        // Feed motor setpoints to motor controller.
        motorController.setPosition(motionPlanner.getMotorPositions());
        motorController.setVelocity(motionPlanner.getMotorVelocities());
        taskControl.acquireLock(motionLock);

        // Do not do anything while in motion.
        while (taskControl.isLockBusy(motionLock) == true) {
            if (motorController.isAtPosition() == true) {
                taskControl.releaseLock(motionLock);
                taskControl.wait(motionTimer, 0.01);  // Wait after motion is completed.
            }
        }
    }
}

auto main(int argc, char** argv) -> int {
    // Instantiate webots robot.
    auto robot = webots::Robot();

    // Spin threads.
    auto t1 = std::thread(simulationSteps, std::ref(robot));
    auto t2 = std::thread(realTimeSteps, std::ref(robot));

    // Wait for threads to finish.
    t1.join();
    t2.join();

    return 0;
}