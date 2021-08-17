#include <Python.h>

#include "CVPuckYou.h"

#include <iostream>
#include <thread>

#include <webots/Robot.hpp>

#include "DeadReckoning.hpp"
#include "EPuckMotionPlanner.hpp"
#include "MotorController.hpp"
#include "SimpleTeleoperation.hpp"
#include "TaskControl.hpp"

// Perform simulation steps until Webots is stopping the controller.
static auto simulationSteps(webots::Robot& robot) -> void {
    auto const timeStep = robot.getBasicTimeStep();
    while (robot.step(timeStep) != -1) {
    }
}

// Perform real-time steps.
// This function contains the control loop logic for the EPuck playing as the mouse. It is
// teleoperated.
static auto mouse(webots::Robot& robot) -> void {
    // Instantiate our task controller class.
    auto taskControl = mtrn4110::TaskControl(robot, 1, 0);

    // Instantiate RSA elements.
    auto teleoperation = mtrn4110::SimpleTeleoperation(robot);
    auto trajectoryPlanner = mtrn4110::DeadReckoning('\0');
    auto motionPlanner = mtrn4110::EPuckMotionPlanner();
    auto motorController = mtrn4110::MotorController(robot);

    // Enter control loop.
    while (1) {
        // Get teleoperation motion command.
        teleoperation.readInput();
        std::cout << teleoperation;

        // Calculate the trajectory.
        trajectoryPlanner.updateMotion(teleoperation.getDeliberatedValue());
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
        taskControl.acquireLock(0);

        // Acquire lock.
        while (taskControl.isLockBusy(0) == true) {
            if (motorController.isAtPosition() == true) {
                taskControl.releaseLock(0);
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