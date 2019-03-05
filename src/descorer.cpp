#include "main.h"
namespace descorer {

    okapi::Logger *log = okapi::Logger::instance();

    okapi::Motor descorer(DESCORER, true, okapi::AbstractMotor::gearset::red);
    double ratio = DESCORER_RATIO;
    int maxVel = 100;

    int toggleCount = 0;
    okapi::QAngle absoluteTarget(0_deg);

    bool isCalibrating = false;
    bool hasTared = false;

    void init() {
        descorer.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
        if (!hasTared) {
            descorer.tarePosition();
            hasTared = true;
        }
    }

    void compInit() {
        descorer.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
        if (hasTared) {
            descorer.tarePosition();
            hasTared = true;
        }
    }
    
    void move() {
        if (!isCalibrating) {
            switch(toggleCount) {
                case 1:
                    maxVel = 200;
                    absoluteTarget = 50_deg; // down
                    break;
                case 2:
                    maxVel = 200;
                    absoluteTarget = 120_deg; // a little bit up to flip flags and lift caps while driving
                    //absoluteTarget = 150_deg;
                    break;
                case 3:
                    maxVel = 200;
                    absoluteTarget = 210_deg; // full send (370)
                    break;
                case 4: // most useful case
                    maxVel = 200;
                    absoluteTarget = 10_deg;
                    break;
                case 5:
                    maxVel = 200;
                    absoluteTarget = 150_deg;
                    break;
                default:
                    maxVel = 200;
                    toggleCount = 1; // default to down
                    absoluteTarget = 90_deg;
                    break;
            }
        }

        descorer.moveAbsolute(absoluteTarget.convert(degree) * ratio, maxVel);
        //printf("Moving to %1.2f\n", absoluteTarget.convert(degree));
    }

    okapi::ControllerButton btnLUF(okapi::ControllerDigital::L1, false);
    okapi::ControllerButton btnD(okapi::ControllerDigital::down);
    okapi::ControllerButton btnRUF(okapi::ControllerDigital::R1);
    okapi::ControllerButton btnRDF(okapi::ControllerDigital::R2);
    okapi::ControllerButton btnB(okapi::ControllerDigital::B);


    void changeState() {
        if (btnLUF.changedToPressed()) {
            toggleCount = (toggleCount < 3) ? (toggleCount + 1) : 1; // count up 1 2 3 4, 1 2 3 4
            //if (++toggleCount >= 5) toggleCount = 1;
        }

        // if (btnD.changedToPressed()) {
        //     toggleCount = (toggleCount > 1) ? (toggleCount - 1) : 1; // count down by one step but stop at 1
        // }
        
		if (btnB.changedToPressed()) {
			toggleCount = 4;
		}

        // if (btnRDF.changedToPressed()) {
        //     toggleCount = (toggleCount < 3) ? (toggleCount + 1) : 1; // count up 1 2 3 4, 1 2 3 4
        //     //if (++toggleCount >= 5) toggleCount = 1;
        // }

        // if (btnRUF.changedToPressed()) {
        //     toggleCount = (toggleCount > 1) ? (toggleCount - 1) : 3; // count down by one step but stop at 1
        // }

        // if (btnRDF.isPressed()) {
        //     toggleCount = 3;
        // } else if (btnRUF.isPressed()) {
        //     toggleCount = 5;
        //     intake::forwardSpin();
        // } else {
        //     toggleCount = 1;
        // }

        if (!isCalibrating) {
            switch(toggleCount) {
                case 1:
                    maxVel = 200;
                    absoluteTarget = 50_deg; // down
                    break;
                case 2:
                    maxVel = 200;
                    absoluteTarget = 170_deg; // a little bit up to flip flags and lift caps while driving
                    //absoluteTarget = 150_deg;
                    break;
                case 3:
                    maxVel = 200;
                    absoluteTarget = 210_deg; // full send (370)
                    break;
                case 4: // most useful case
                    maxVel = 200;
                    absoluteTarget = 10_deg;
                    break;
                case 5:
                    maxVel = 200;
                    absoluteTarget = 150_deg;
                    break;
                default:
                    maxVel = 200;
                    toggleCount = 1; // default to down
                    absoluteTarget = 90_deg;
                    break;
            }
        }
        std::string state = std::to_string(toggleCount) + "\n";
        //printf(state.c_str());
        //log->info("Flipper Target: " + std::to_string(absoluteTarget.convert(degree)) + ", " + "toggleCount: " + std::to_string(toggleCount));
    }

    // 352 to get balls off cap
    // 150 to prep
    // 240 to flippo flaggo
    void moveTarget(int target) {
        descorer.moveAbsolute(target, 200);
    }

    void moveTarget(int target, int speed) {
        descorer.moveAbsolute(target, speed);
    }

    void changeState(int count) {
        toggleCount = count;
    }

    void calibrate(void* p) {
        isCalibrating = true;
        while (isCalibrating) {
            descorer.moveVelocity(-50);
            if (descorer.getActualVelocity() < 10) {
                descorer.tarePosition();
                break;
            }
            pros::delay(10);
        }
    }

    void waitUntilSettled() {
        while (abs(descorer.getActualVelocity()) > 50 && abs(descorer.getTargetPosition() - descorer.getPosition()) > 10) {
            pros::delay(20);
        }
    }
}