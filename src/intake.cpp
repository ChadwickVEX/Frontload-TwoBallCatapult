#include "main.h"

namespace intake {
    okapi::Motor intake(INTAKE);

    okapi::ControllerButton intakeOut(okapi::ControllerDigital::R1, false);
    okapi::ControllerButton intakeIn(okapi::ControllerDigital::R2, false);

    void move() {
        int go = intakeIn.isPressed() - intakeOut.isPressed();
        intake.moveVoltage(12000 * go);
    }

    void forwardSpin() {
        intake.moveVoltage(-12000);
    }

    void backwardSpin() {
        intake.moveVoltage(12000);
    }

    void stop() {
        intake.setBrakeMode(AbstractMotor::brakeMode::coast);
        intake.moveVoltage(0);
    }
}