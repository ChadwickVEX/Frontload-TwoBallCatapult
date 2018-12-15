#include "visioncontrol.hpp"
#include "drive.hpp"
#include "main.h"

namespace visionControl {

    okapi::Logger *log = okapi::Logger::instance();

    pros::Vision vision(VISION_SENSOR_PORT, pros::E_VISION_ZERO_CENTER);
    Controller controller;

    double SIG_1_SENS = 1.4; // red flag
    double SIG_2_SENS = 1.4; // blue flag
    double SIG_3_SENS = 1.4; // green part

    pros::vision_color_code_t ccRedFlag;
    pros::vision_color_code_t ccBlueFlag;

    tTargetingState lastState = notTargeting;
    tTargetingState currState = notTargeting;

    bool isOnTarget = false;
    
    const double kP = 0.075;
    const double kI = 0.01;
    const double kD = 25.0;

    auto anglePIDController = IterativeControllerFactory::posPID(kP, kI, kD, 0, std::make_unique<AverageFilter<5>>());

    void init() {
        ccRedFlag = vision.create_color_code(1, 3); // 0 = green part, 2 = red part
        ccBlueFlag = vision.create_color_code(3, 2); // 0 = green part, 1 = blue part

        // pros::vision_signature_s_t blue = vision.get_signature(2);
        // blue.range = SIG_2_SENS;
        // vision.set_signature(2, &blue);

        // pros::vision_signature_s_t red = vision.get_signature(1);
        // red.range = SIG_1_SENS;
        // vision.set_signature(1, &red);

        // pros::vision_signature_s_t green = vision.get_signature(3);
        // green.range = SIG_3_SENS;
        // vision.set_signature(3, &green);

        pros::Task targetingTask(move, (void*)1, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Targeting Move");
    }

    void action() { // remember to make this not fight opcontrol controller
        double speed = 0;
        pros::vision_object_s_t flagObj;
        log->debug("Angle to Blue Flag: " + std::to_string(vision.get_by_code(0, ccBlueFlag).angle));
        log->debug("Angle to Red Flag: " + std::to_string(vision.get_by_code(0, ccRedFlag).angle));
        log->debug("X Position of Green Thing: " + std::to_string(vision.get_by_sig(0, 3).x_middle_coord));
    
        switch (currState) {
            case notTargeting:
                break;
            
            // case redFlag algorithm:
            // Get all the codes, take the closest one and aim at it
            // API call: vision.read_by_code()
            // https://pros.cs.purdue.edu/v5/api/cpp/vision.html#read-by-code
            case redFlag:
                anglePIDController.flipDisable(false);

                anglePIDController.setTarget(0);

                flagObj = vision.get_by_code(0, ccRedFlag); // biggest obj of red flag color code
                
                speed = anglePIDController.step(flagObj.angle);

                drive::moveVoltage(-speed, speed);
                if (anglePIDController.isSettled())
                    controller.rumble(". "); // short rumbles if you're done targeting
                break;
            case blueFlag:
                anglePIDController.flipDisable(false);
                
                anglePIDController.setTarget(-180);

                flagObj = vision.get_by_code(0, ccBlueFlag); // biggest object of blue flag color code

                speed = anglePIDController.step(flagObj.x_middle_coord); 

                drive::moveVoltage(-speed, speed);
                if (anglePIDController.isSettled())
                    controller.rumble(". "); // short rumbles if you're done targeting
                break;
            case flag:
            {
                anglePIDController.flipDisable(false);
                if (lastState == notTargeting) {
                    isOnTarget == false;
                }
                anglePIDController.setTarget(0);
                int sizeIndex = 0;
                flagObj = vision.get_by_sig(0, 3); // biggest obj (0) of sig 3
                while (flagObj.y_middle_coord > 120 && currState == flag) { // avoid the bottom half of the screen
                    sizeIndex++; // pick a new one if it's too big
                    flagObj = vision.get_by_sig(sizeIndex, 3);
                }

                if (flagObj.x_middle_coord == 0 || isOnTarget) {
                    speed = 0;
                    isOnTarget == true;
                } else {
                    speed = anglePIDController.step(flagObj.x_middle_coord);
                }

                drive::moveVoltage(-speed, speed);
                if (anglePIDController.isSettled())
                    controller.rumble(". ");
                break;
            }
        }
    }

    void move(void* param) {
        okapi::ControllerButton btnA(okapi::ControllerDigital::A, false);

        while (true) {

            lastState = currState;

            if (btnA.isPressed()) {
                currState = flag;
            } else {
                currState = notTargeting;
            }

            action();

            pros::delay(10);
        }
    }

    tTargetingState getState() {
        return currState;
    }

    void setState(tTargetingState state) {
        currState = state;
    }

    bool isTargeting() {
        switch(currState) {
            case notTargeting:
                return false;
                break;
            case redFlag:
                return true;
                break;
            case blueFlag:
                return true;
                break;
            case flag:
                return true;
                break;
            default:
                return false;
                break;
        }
    }

}
