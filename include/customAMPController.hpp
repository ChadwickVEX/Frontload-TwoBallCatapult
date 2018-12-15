#ifndef _MANAS_CONTROLLER_HPP_
#define _MANAS_CONTROLLER_HPP_

#include "okapi/api/control/async/asyncMotionProfileController.hpp"

namespace okapi {
  class CustomAMPController : public AsyncMotionProfileController {
  public:
    int directionR = 1;
    int directionL = 1;

    using AsyncMotionProfileController::AsyncMotionProfileController;
    
    void executeSinglePath(const TrajectoryPair &path, std::unique_ptr<AbstractRate> rate) override {
      currentPosition = 0;
      pathLength = path.length;
      auto linearSpeedToRotationalSpeed = [&](QSpeed linearMps) -> QAngularSpeed {
        return linearMps * (360_deg / (1_pi * 4.125_in));
      };

      for (int i = 0; i < path.length && !isDisabled(); ++i)
      {
        auto leftRPM = linearSpeedToRotationalSpeed(path.left[i].velocity * mps).convert(rpm) * directionL;
        auto rightRPM = linearSpeedToRotationalSpeed(path.right[i].velocity * mps).convert(rpm) * directionR;
        logger->info(std::to_string(leftRPM /*/ toUnderlyingType(AbstractMotor::gearset::green)*/) + ", " + std::to_string(rightRPM /*/ toUnderlyingType(AbstractMotor::gearset::green)*/));
        model->left(leftRPM / toUnderlyingType(AbstractMotor::gearset::green));
        model->right(rightRPM / toUnderlyingType(AbstractMotor::gearset::green));

        rate->delayUntil(1_ms);
      }
      directionR = 1;
      directionL = 1;
    }

    void turnPath(const QAngle angleDegrees, std::string pathName) {
      double newTarget = fabs(angleDegrees.convert(degree)) * scales.turn * pair.ratio; // number of degrees motor needs to turn
      newTarget =  scales.wheelDiameter.convert(inch) * PI * (newTarget / 360.0); // inches it would travel

      generatePath(
        {{0_in, 0_in, 0_deg},
        {newTarget * inch, 0_in, 0_deg}}, 
        pathName
      );
    }

    /**
     * direction: 1 is right, -1 is left.
     */
    void turnAngle(std::string pathId, int direction) {
      directionR = -1 * direction;
      directionL = 1 * direction;
      setTarget(pathId);
      waitUntilSettled();
      waitUntilPathComplete();
      removePath(pathId);
    }

    bool isPathComplete() {
      return (currentPosition >= pathLength);
    }
    
    void waitUntilPathComplete() {
      while (!isPathComplete()) {
        pros::delay(50);
      }
    }

    /**
     * Execute the next path with the robot reversing.
     * Return: 1 if running forward, -1 running backward.
     */
    int reverse() {
      this->directionR = -1;
      this->directionL = -1;
      return directionR;
    }

    int forward() {
      this->directionR = 1;
      this->directionL = 1;
      return directionR;
    }

    void stop() {
      isRunning = false;
    }

  private:
    int currentPosition;
    int pathLength;

    float mpsToRpm(float mps) {
      // (meters / second) * (60 sec / 1 minute) * (1 inch / 0.0254 meters) * (1 rotation / (diameter * pi)
      float rpm = (mps * 60.0) / (0.0254 * 4.125 * PI);
      return rpm;
    }
  };
}

#endif

