#include <webots/DistanceSensor.hpp>
#include <webots/Motor.hpp>
#include <webots/Robot.hpp>
#include <webots/Keyboard.hpp>
#include <webots/GPS.hpp>
#include <webots/InertialUnit.hpp>
#include <webots/Camera.hpp>


#define TIME_STEP 64
using namespace webots;

int main(int argc, char **argv) {
  Robot *robot = new Robot();
  
  
  Camera *cm;
  cm=robot->getCamera("camera");
  cm->enable(TIME_STEP);
  
  
  delete robot;
  return 0;  // EXIT_SUCCESS
}
