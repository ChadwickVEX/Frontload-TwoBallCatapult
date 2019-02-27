#include "main.h"
namespace descorer {

    okapi::Logger *log = okapi::Logger::instance();

    okapi::Motor descorer(DESCORER, true, okapi::AbstractMotor::gearset::red);
    double ratio = DESCORER_RATIO;
    int maxVel = 100;

    int toggleCount = 0;
    okapi::QAngle absoluteTarget(0_deg);

    void init() {
        descorer.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
        descorer.tarePosition();
    }

    void compInit() {
        descorer.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
        descorer.tarePosition();
    }
    
    void move() {
        switch(toggleCount) {
            case 1:
                maxVel = 200;
                absoluteTarget = 50_deg; // down
                break;
            case 2:
                maxVel = 100;
                absoluteTarget = 120_deg; // a little bit up to flip flags and lift caps while driving
                break;
            case 3:
                maxVel = 100;
                absoluteTarget = 210_deg; // full send (370)
                break;
            case 4: // most useful case
                maxVel = 100;
                absoluteTarget = 10_deg;
                break;
            default:
                maxVel = 200;
                toggleCount = 1; // default to down
                absoluteTarget = 90_deg;
                break;
        }

        descorer.moveAbsolute(absoluteTarget.convert(degree) * ratio, maxVel);
        //printf("Moving to %1.2f\n", absoluteTarget.convert(degree));
    }

    okapi::ControllerButton btnLUF(okapi::ControllerDigital::L1, false);
    okapi::ControllerButton btnD(okapi::ControllerDigital::down);
    okapi::ControllerButton btnRUF(okapi::ControllerDigital::R1);
    okapi::ControllerButton btnRDF(okapi::ControllerDigital::R2);

    void changeState() {
        // if (btnLUF.changedToPressed()) {
        //     toggleCount = (toggleCount < 5) ? (toggleCount + 1) : 1; // count up 1 2 3 4, 1 2 3 4
        //     //if (++toggleCount >= 5) toggleCount = 1;
        // }

        // if (btnD.changedToPressed()) {
        //     toggleCount = (toggleCount > 1) ? (toggleCount - 1) : 1; // count down by one step but stop at 1
        // }

        if (btnRUF.changedToPressed()) {
            toggleCount = (toggleCount < 5) ? (toggleCount + 1) : 1; // count up 1 2 3 4, 1 2 3 4
            //if (++toggleCount >= 5) toggleCount = 1;
        }

        if (btnRDF.changedToPressed()) {
            toggleCount = (toggleCount > 1) ? (toggleCount - 1) : 5; // count down by one step but stop at 1
        }

        switch(toggleCount) {
            case 1:
                maxVel = 200;
                absoluteTarget = 50_deg; // down
                break;
            case 2:
                maxVel = 100;
                absoluteTarget = 120_deg; // a little bit up to flip flags and lift caps while driving
                break;
            case 3:
                maxVel = 100;
                absoluteTarget = 210_deg; // full send (370)
                break;
            case 4: // most useful case
                maxVel = 100;
                absoluteTarget = 10_deg;
                break;
            default:
                maxVel = 200;
                toggleCount = 1; // default to down
                absoluteTarget = 90_deg;
                break;
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

    void waitUntilSettled() {
        while (abs(descorer.getActualVelocity()) > 50 && abs(descorer.getTargetPosition() - descorer.getPosition()) > 10) {
            pros::delay(20);
        }
    }
}