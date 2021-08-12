#include <thread>
#include <webots/Robot.hpp>

#include "DeadReckoning.hpp"
#include "DistanceSensor.hpp"
#include "EPuckMotionPlanner.hpp"
#include "HCDeliberator.hpp"
#include "HCLocaliser.hpp"
#include "LidarSensor.hpp"
#include "MotorController.hpp"
#include "PathSequencer.hpp"
#include "TaskControl.hpp"

// Perform simulation steps until Webots is stopping the controller.
static auto simulationSteps(webots::Robot& robot) -> void {
    auto const timeStep = robot.getBasicTimeStep();
    while (robot.step(timeStep) != -1) {
    }
}

// Perform real-time steps.
static auto realtimeSteps(webots::Robot& robot) -> void {
    // Instantiate our task controller class.
    auto taskControl = mtrn4110::TaskControl(2, 2);
    (void)taskControl;

    // Instantiate RSA elements.
    auto distanceSensor = mtrn4110::DistanceSensor(robot);
    (void)distanceSensor;
    auto lidarSensor = mtrn4110::LidarSensor(robot);
    (void)lidarSensor;
    auto motorController = mtrn4110::MotorController(robot);
    (void)motorController;
    auto motionPlanner = mtrn4110::EPuckMotionPlanner(0, 0);
    (void)motionPlanner;
    auto deadReckoning = mtrn4110::DeadReckoning(' ');
    (void)deadReckoning;
    auto pathSequencer = mtrn4110::PathSequencer({'F', 'L', 'R'});
    (void)pathSequencer;
    auto hcLocaliser = mtrn4110::HCLocaliser({0, 0}, 2);
    (void)hcLocaliser;
    auto hcDeliberator = mtrn4110::HCDeliberator();
    (void)hcDeliberator;
    // Enter control loop.
    while (1) {
    }
}

auto main(int argc, char** argv) -> int {
    (void)argc;
    (void)argv;

    // Instantiate webots robot.
    auto robot = webots::Robot();

    // Spin threads.
    auto t1 = std::thread(simulationSteps, std::ref(robot));
    auto t2 = std::thread(realtimeSteps, std::ref(robot));

    // Wait for threads to finish.
    t1.join();
    t2.join();

    return 0;
}