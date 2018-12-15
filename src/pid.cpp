#include "main.h"

PID::PID (double kP, double kI, double kD, int target) {
    this->kP = kP;
    this->kI = kI;
    this->kD = kD;
    lastTime = pros::millis();
    this->target = target;
    error = target;
} // todo make second constructor to use legacy sensors

/**
 * Next PID step.
 * Constrained between [-1, 1]
 */
double PID::next(int reading) {
    dT = pros::millis() - lastTime;
    double speed = 0.0;

    lastError = error;
    error = target - reading;
    double derivative = (double) error / ((double) dT);
    double integral = 0;

    // todo implement all of pid lul
    // note sum integral for only last x errors
    // --> average derivative within a window

    speed = (error * kP) + (derivative * kD) + (integral * kI);

    if (speed < -1)
        speed = -1.0;
    if (speed > 1)
        speed = 1.0;

    lastTime += dT;
    return speed;
}

void PID::changeTarget(int target) {
    this->target = target;
}

