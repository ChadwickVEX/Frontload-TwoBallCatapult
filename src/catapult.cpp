#include "main.h"
#include "config.hpp"
#include "descorer.hpp"

namespace catapult {

    okapi::Motor catapult1(CATAPULT_1, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    okapi::Motor catapult2(CATAPULT_2, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);

    okapi::MotorGroup catapult({-CATAPULT_1, CATAPULT_2});

    okapi::ControllerButton btnFLD(okapi::ControllerDigital::L2, false);
    okapi::ControllerButton btnPadUp(okapi::ControllerDigital::up, false);
    okapi::ControllerButton btnPadRight(okapi::ControllerDigital::right, false);
    okapi::ADIButton catapultLimit(CATAPULT_LIM);

    tCatapultState lastState = shooting;
    tCatapultState currState = lowering;

    okapi::Logger *logger = okapi::Logger::instance();

    void tare() {
        catapult1.tarePosition();
        catapult2.tarePosition();
    }

    /**
     * TODO
     * Tune where current draw causes resistance
     * Tune what angle to turn to
     */

    void calibrate() {
        // spin it until you feel resistance and then stop and set 0
        while (catapult1.getCurrentDraw() < SLIP_CURRENT_DRAW /* needs tuning */) {
            catapult1.moveVelocity(200);
            catapult2.moveVelocity(200);
            pros::delay(10);
        }
        tare();
    }

    void changeState(tCatapultState state) {
        currState = state;
    }

    tCatapultState updateState() {
        lastState = currState;
        if (btnFLD.changedToPressed()) {
            currState = shooting;
        }
        if (btnFLD.changedToReleased()) {
            currState = lowering;
        }
        if (btnPadUp.changedToPressed()) {
            currState = movingBall;
        }
        if (btnPadRight.changedToPressed()) {
            currState = unmoving;
        }
        return currState;
    }

    std::string getStateString() {
        switch(currState) {
            case lowered:
                return "lowered";
            case lowering:
                return "lowering";
            case shooting:
                return "shooting";
            case movingBall:
                return "moving ball";
            case unmoving:
                return "not moving catapult";
        }
    }

    void simpleMove() {
        int power = (btnFLD.isPressed() - btnPadUp.isPressed()) * 12000;
        if (power == 0) {
            catapult1.setBrakeMode(AbstractMotor::brakeMode::hold);
            catapult2.setBrakeMode(AbstractMotor::brakeMode::hold);
            catapult1.moveVelocity(0);
            catapult2.moveVelocity(0);
        } else {
            catapult1.moveVoltage(power);
            catapult2.moveVoltage(power);
        }
    }

    void prepareLoad() {
        catapult1.setBrakeMode(AbstractMotor::brakeMode::hold);
        catapult2.setBrakeMode(AbstractMotor::brakeMode::hold);
        while (catapult1.getCurrentDraw() < SLIP_CURRENT_DRAW) {
            catapult1.moveVoltage(12000);
            catapult2.moveVoltage(12000);
        }
        catapult1.moveRelative(LOAD_TARGET, 200);
        catapult2.moveRelative(LOAD_TARGET, 200);
    }

    void move(void* arg) {
        int shootingRuns = 0;
        bool isLowered = false;

        while (true) {
            //Logger::initialize(std::make_unique<Timer>(), "/ser/sout", Logger::LogLevel::info);
            switch (currState) {
                case lowering:
                    catapult.setBrakeMode(AbstractMotor::brakeMode::hold);
                    if (catapultLimit.isPressed()) {
                        catapult.moveVelocity(0);
                        isLowered = true;
                    } else {
                        isLowered = false;
                        catapult.moveVoltage(12000);
                    }
                    break;
                case shooting:
                    isLowered = false;
                    catapult.setBrakeMode(AbstractMotor::brakeMode::coast);
                    catapult.moveVoltage(12000);
                    descorer::changeState(2);
                    break;
                case movingBall:
                    if (lastState == lowering && isLowered) {
                        catapult.tarePosition();
                    } else if(!isLowered) {
                        currState = lowering;
                        lastState = movingBall;
                        break;
                    }
                    catapult.moveVoltage(-6000);
                    if (abs(catapult.getPosition()) >= (50 * 7)) {
                        catapult.moveVoltage(8000);
                        currState = lowering;
                        lastState = movingBall;
                        break;
                    }
                    break;
                case unmoving:
                    catapult.setBrakeMode(AbstractMotor::brakeMode::coast);
                    catapult.moveVoltage(0);
                    break;
            }
            
            // if (pros::competition::is_autonomous()) {
            //     switch (currState) {
            //         case shooting:
            //             shootingRuns += 1; // 70 allowed to shoot, 70 / 1 = 70, 70 * 10 = 700 ms allowed total
            //             if (shootingRuns >= 70) {
            //                 currState = lowering;
            //                 shootingRuns = 0;
            //             }
            //             break;
            //         case lowering:
            //             break;
            //     }
            // }
            pros::Task::delay(10);
        }
    }

    // logger functions

    void initializeLogger() {
        Logger::initialize(std::make_unique<Timer>(), "/ser/sout", Logger::LogLevel::info);
    }

    void logCurrentDraw() {
        logger->info("catapult current draw: " + std::to_string(catapult.getCurrentDraw()));
        logger->info("catapult torque: " + std::to_string(catapult.getTorque()));
    }

    void logAngle() {
        logger->info("catapult angle: " + std::to_string(catapult.getPosition()));
    }

    void logState() {
        logger->info("catapult state: " + getStateString());
    }
}