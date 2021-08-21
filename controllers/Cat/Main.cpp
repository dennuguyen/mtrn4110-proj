#include <Python.h>

#include <algorithm>
#include <iostream>
#include <thread>

#include <webots/Robot.hpp>

// Used exclusively in autonomous control.
#include "BFSDFS.hpp"
#include "CVProcessor.hpp"
#include "Camera.hpp"
#include "Grapher.hpp"
#include "PathSequencer.hpp"

// Used in both teleoperation and autonomous control.
#include "DeadReckoning.hpp"
#include "EPuckMotionPlanner.hpp"
#include "LidarSensor.hpp"
#include "MotorController.hpp"
#include "SimpleTeleoperation.hpp"

// Extra control over control loop.
#include "Models.hpp"
#include "TaskControl.hpp"

// Perform simulation steps until Webots is stopping the controller.
static auto simulationSteps(webots::Robot& robot) -> void {
    auto const timeStep = robot.getBasicTimeStep();
    while (robot.step(timeStep) != -1) {
    }
}

// Perform real-time steps.
// This function contains the control loop logic for the EPuck. It supports both autonomous control
// and teleoperation.
static auto realTimeSteps(webots::Robot& robot) -> void {
    // Instantiate our task controller class.
    auto taskControl = mtrn4110::TaskControl(robot, 3, 1);
    auto constexpr modeLock = 0;  // true = teleoperation, false = autonomous
    auto constexpr motionLock = 1;  // true = in motion, false = not in motion

    // These RSA elements are exclusive to autonomous control.
    auto camera = mtrn4110::Camera(robot);
    auto cvProcessor = mtrn4110::CVProcessor();
    auto grapher = mtrn4110::Grapher();
    auto pathPlanner = mtrn4110::BFSDFS();
    auto pathSequencer = mtrn4110::PathSequencer();

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

        // Toggle operation modes.
        if (key == ' ') {
            if (taskControl.isLockBusy(modeLock) == false) {
                std::cout << "Teleoperating!" << std::endl;
                taskControl.acquireLock(modeLock);
            }
            else {
                std::cout << "Autonomous!" << std::endl;
                taskControl.releaseLock(modeLock);
            }
            continue;  // Invalidate the deliberated value.
        }

        // In autonomous mode so perform autonomous operations.
        if (taskControl.isLockBusy(modeLock) == false) {
            // Get image of map.
            camera.snap(mtrn4110::files::mazeImage, 100);

            // Map the image.
            cvProcessor.localise(mtrn4110::files::mazeImage);
            cvProcessor.waypoint(mtrn4110::files::mazeImage, mtrn4110::files::mouseImage);
            cvProcessor.map(mtrn4110::files::mazeImage);

            // Create a graph from the map.
            auto const graph = grapher.buildGraph(cvProcessor.getMap());

            // Compute a path plan from the graph with a destination, starting position and
            // starting heading.
            pathPlanner.update(graph,
                               cvProcessor.getDeliberatedValue(),
                               cvProcessor.getCurrentPose(),
                               cvProcessor.getCurrentHeading());
            std::cout << pathPlanner;
            std::cout << (pathPlanner << cvProcessor).str();

            // Give the path sequencer the path plan.
            pathSequencer.resetPath(pathPlanner.getPath());

            // Get next motion in path plan.
            motion = pathSequencer.nextMotion();
        }
        else {
            motion = teleoperation.getDeliberatedValue();
        }

        // If about to move forwards into an obstacle, 99% chance it's the mouse so cat wins.
        // TODO: not working because lidar rays go thru epuck's turret slot space.
        // if (lidarSensor.detectCardinal(mtrn4110::models::maze.distanceBetweenCells / 2, 10,
        // 0.5)[1]
        //     && motion == 'F') {
        //     std::cout << "GAME OVER" << std::endl;
        //     return;
        // }

        // Calculate the trajectory.
        trajectoryPlanner.updateMotion(motion);
        trajectoryPlanner.computeTrajectory({0.016, 0, 0}, {0, 0, 0.05});

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