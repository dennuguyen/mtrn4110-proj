#include <thread>
#include <webots/Robot.hpp>

#include "TaskControl.hpp"
#include "Timer.hpp"

// Perform simulation steps until Webots is stopping the controller.
static auto simulationSteps(webots::Robot &robot) -> void {
    auto const timeStep = robot.getBasicTimeStep();
    while (robot.step(timeStep) != -1) {
    }
}

// Perform real-time steps.
static auto realtimeSteps(mtrn4110::TaskControl &taskControl) -> void {
    // constexpr auto csvPath = "../../MotionExecution.csv";
    // constexpr auto mapPath = "../../Map.txt";
    // constexpr auto pathPlanPath = "../../PathPlan.txt";
    (void)taskControl;
    // Enter control loop.
    while (1) {
    }
}

auto main(int argc, char **argv) -> int {
    (void)argc;
    (void)argv;

    // Instantiate webots robot.
    auto robot = webots::Robot();

    // Instantiate our task controller class.
    auto taskControl = mtrn4110::TaskControl(robot);

    // Spin threads.
    auto t1 = std::thread(simulationSteps, std::ref(robot));
    auto t2 = std::thread(realtimeSteps, std::ref(taskControl));

    // Wait for threads to finish.
    t1.join();
    t2.join();

    return 0;
}
