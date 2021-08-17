#include <Python.h>

#include <iostream>
#include <thread>

#include <webots/Robot.hpp>

// Used exclusively in autonomous control.
#include "CVPuckYou.h"
#include "DistanceSensor.hpp"
#include "Grapher.hpp"
#include "PathSequencer.hpp"

// Used in both teleoperation and autonomous control.
#include "DeadReckoning.hpp"
#include "EPuckMotionPlanner.hpp"
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
// This function contains the control loop logic for the EPuck. It supports both autonomous control
// and teleoperation.
static auto mouse(webots::Robot& robot) -> void {
    // Instantiate our task controller class.
    auto taskControl = mtrn4110::TaskControl(robot, 2, 0);
    using modeLock = 0;  // true = teleoperation, false = autonomous
    using motionLock = 1;

    // These RSA elements are exclusive to autonomous control.
    auto distanceSensor = mtrn4110::DistanceSensor(robot);
    // auto lidarSensor = mtrn4110::LidarSensor(robot);
    auto deliberator = mtrn4110::HCDeliberator();
    auto localiser = mtrn4110::HCLocaliser({0, 0}, 2);
    auto grapher = mtrn4110::Grapher();
    auto pathSequencer = mtrn4110::PathSequencer({});

    // These RSA elements are used in both teleoperation and autonomous control.
    auto teleoperation = mtrn4110::SimpleTeleoperation(robot);
    auto trajectoryPlanner = mtrn4110::DeadReckoning('\0');
    auto motionPlanner = mtrn4110::EPuckMotionPlanner();
    auto motorController = mtrn4110::MotorController(robot);

    // Enter control loop.
    while (1) {
        auto motion = '\0';

        // Get teleoperation motion command.
        auto const key = teleoperation.readInput();

        // Toggle operation modes.
        if (key == ' ') {
            if (taskControl.isLockBusy(modeLock) == true) {
                std::cout << "Teloperating!" << std::endl;
                taskControl.acquireLock(modeLock);
            }
            else {
                std::cout << "Autonomous!" << std::endl;
                taskControl.releaseLock(modeLock);
            }
        }

        // In autonomous mode so perform autonomous operations.
        if (taskControl.isLockBusy(modeLock) == false) {
            // TODO: EVERYTHING IN THIS IF STATEMENT

            // Get image of map.
            // camera.snap(mtrn4110::files::mazeImage);

            // Map the image.
            // auto const map = std::string(runCVMapper(mtrn4110::files::mazeImage));

            // // Graph map.
            // grapher.readMap(map);
            // grapher.buildGraph();

            // // Deliberate.
            // auto const destination = runCVWaypointer(mtrn4110::files::mazeImage);

            // // Localise.
            // auto const [pose, heading] =
            //     runCVLocaliser(mtrn4110::files::mazeImage, mtrn4110::files::ladybugImage);

            // // Path plan.
            // // if ()
            // // pathPlanner.updateDestination();

            // // Path sequencer.
            // motion = pathSequencer.nextMotion();
        }
        else {
            motion = teleoperation.getDeliberatedValue();
        }

        // Calculate the trajectory.
        trajectoryPlanner.updateMotion(motion);
        trajectoryPlanner.computeTrajectory({0.1, 0, 0}, {0, 0, 1});
        std::cout << trajectoryPlanner;

        // Calculate the motor setpoints for current trajectory.
        auto const angle = trajectoryPlanner.getAngle();
        auto const distance = trajectoryPlanner.getDistance();
        auto const linearVelocity = trajectoryPlanner.getLinearVelocity();
        auto const angularVelocity = trajectoryPlanner.getAngularVelocity();
        motionPlanner.computeMotorSetpoints(angle, distance, linearVelocity, angularVelocity);
        std::cout << motionPlanner;

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
    // Startup Python interpretter.
    if (PyImport_AppendInittab("CVPuckYou", PyInit_CVPuckYou) == -1) {
        throw std::runtime_error("Could not extend built-in modules table.");
    }
    Py_Initialize();

    // Import CVPuckYou into the Python interpretter.
    auto module = PyImport_ImportModule("CVPuckYou");
    if (module == nullptr) {
        PyErr_Print();
        throw std::runtime_error("Could not import CVPuckYou.");
    }

    // Instantiate webots robot.
    auto robot = webots::Robot();

    // Spin threads.
    auto t1 = std::thread(simulationSteps, std::ref(robot));
    auto t2 = std::thread(mouse, std::ref(robot));

    // Wait for threads to finish.
    t1.join();
    t2.join();

    // End the Python interpretter.
    Py_Finalize();

    return 0;
}