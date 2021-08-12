#include <thread>
#include <webots/Robot.hpp>

#include "DeadReckoning.hpp"
#include "DistanceSensor.hpp"
#include "EPuckMotionPlanner.hpp"
#include "HCDeliberator.hpp"
#include "HCLocaliser.hpp"
#include "HCPathPlanner.hpp"
#include "LidarSensor.hpp"
#include "MotorController.hpp"
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
    auto lidarSensor = mtrn4110::LidarSensor(robot);
    auto motorController = mtrn4110::MotorController(robot);
    auto motionPlanner = mtrn4110::EPuckMotionPlanner(0, 0);
    auto deadReckoning = mtrn4110::DeadReckoning(' ');
    auto hcPathPlanner = mtrn4110::HCPathPlanner(NULL, {0, 0}, {0, 0}, 2);
    auto hcLocaliser = mtrn4110::HCLocaliser({0, 0}, 2);
    auto hcDeliberator = mtrn4110::HCDeliberator({});
    (void)distanceSensor;
    (void)lidarSensor;
    (void)motorController;
    (void)motionPlanner;
    (void)deadReckoning;
    (void)hcLocaliser;
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