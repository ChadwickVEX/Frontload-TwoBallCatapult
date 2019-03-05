#include "odometry.hpp"

namespace odometry
{
ADIEncoder rightEnc(RIGHT_ENC.front(), RIGHT_ENC.back(), false);
ADIEncoder leftEnc(LEFT_ENC.front(), LEFT_ENC.back());

double rEncLast;
double lEncLast;

const double CHASSISWIDTH = 4.736111111; // was 6.42
const double TICKSINCH = ENC_WHEEL * PI / 360.0;

QLength currX;
QLength currY;
QAngle currAngle;

bool appOn;

void init()
{
    //rightEnc.reset();
    //leftEnc.reset();
    currX = 0_ft;
    currY = 0_ft;
    currAngle = 0_deg;

    rEncLast = rightEnc.get() * TICKSINCH;
    lEncLast = leftEnc.get() * TICKSINCH;

    appOn = false;
}

/**
     * Iterate
     */
void calculate()
{
    using namespace okapi;

    double dX = 0.0;
    double dY = 0.0;
    double dTheta = 0.0;

    double rCurrEnc = rightEnc.get() * TICKSINCH;
    double lCurrEnc = leftEnc.get() * TICKSINCH;

    double rDEnc = rCurrEnc - rEncLast;
    double lDEnc = lCurrEnc - lEncLast;

    double dCenterArc = (rDEnc + lDEnc) / 2.0;
    // dCenterArc *= TICKSINCH;

    dTheta = (lDEnc - rDEnc) / CHASSISWIDTH /** PI / 180.0*/;

    double radius = (dTheta == 0) ? 0 : dCenterArc / dTheta;
    dX = dTheta == 0 ? 0 : (radius - radius * cos(dTheta));
    dY = dTheta == 0 ? dCenterArc : radius * sin(dTheta);

    currX = (dX * cos(currAngle.convert(radian)) + dY * sin(currAngle.convert(radian)) + currX.convert(inch)) * inch;
    currY = (dY * cos(currAngle.convert(radian)) - dX * sin(currAngle.convert(radian)) + currY.convert(inch)) * inch;

    QAngle tempCurrAngle = ((dTheta * 180.0 / PI) + currAngle.convert(degree)) * degree;

    rEncLast = rCurrEnc;
    lEncLast = lCurrEnc;

    while (tempCurrAngle.convert(degree) >= 360.0)
    {
        tempCurrAngle = (tempCurrAngle.convert(degree) - 360.0) * degree;
    }
    while (tempCurrAngle.convert(degree) < 0.0)
    {
        tempCurrAngle = (tempCurrAngle.convert(degree) + 360.0) * degree;
    }

    currAngle = tempCurrAngle;
}

QLength distanceToPoint(QLength x, QLength y) {
    return (sqrt(pow((currX.convert(inch) - x.convert(inch)), 2) + pow((currY.convert(inch) - y.convert(inch)), 2))) * inch;
}

QAngle angleToPoint(QLength x, QLength y) {}

std::tuple<QLength, QAngle> distanceAndAngleToPoint(QLength x, QLength y)
{
    return std::tuple<QLength, QAngle>(distanceToPoint(x, y), angleToPoint(x, y));
}

void printPosition(void *p)
{
    pros::Controller controller(pros::E_CONTROLLER_MASTER);
    controller.clear();
    int count = 0;
    int startTime = 0;
    using namespace okapi;

    while (true)
    {
        double x = currX.convert(okapi::foot);
        double y = currY.convert(okapi::foot);
        double left = leftEnc.get();
        double right = rightEnc.get();
        double angle = currAngle.convert(degree);
        controller.print(0, 0, "X: %.2f", x);
        //controller.print(0, 0, "L: %.2f", left);
        if (pros::competition::is_autonomous() && count < 1 && !pros::competition::is_disabled()) {
            count++;
            startTime = pros::millis();
        } else if (pros::competition::is_autonomous() && !pros::competition::is_disabled()) {
            double deltaT =  ((double) (pros::millis() - startTime)) / 1000.0;
            //controller.print(0, 0, "Time: %1.2f", deltaT);
        }
        pros::delay(51);
        controller.print(1, 0, "Y: %.2f", y);
        //controller.print(1, 0, "R: %.2f", right);
        pros::delay(51);
        controller.print(2, 0, "A: %1.2f", angle);
        //controller.print(2, 0, "app: %d", (appOn) ? 1 : 0);
        pros::delay(51);
    }
}

void run(void *p)
{
    pros::Task odometryPrint(printPosition, nullptr, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Position Print --> Controller");
    while (true)
    {
        calculate();
        pros::delay(5);
    }
}

void turnAbsolute(QAngle target)
{
    double angleError = target.convert(okapi::radian) - currAngle.convert(okapi::radian);
    angleError = atan2(sin(angleError), cos(angleError));

    // pros::Controller controller(pros::E_CONTROLLER_MASTER);

    // pros::delay(51);
    // controller.print(1, 0, "AE: %1.2f", angleError * 180.0/PI);
    // pros::delay(51);
    // controller.print(2, 0, "A: %1.2f", currAngle.convert(degree));
    // pros::delay(51);
    QAngle targetAng = (angleError * 180.0 / PI) * degree;
    // controller.print(0, 0, "AE2: %1.2f", targetAng.convert(degree));

    chassis.turnAngle(targetAng);

    // okapi::IterativePosPIDController tc = okapi::IterativeControllerFactory::posPID(0.41, 0.01, 0.01, 0, std::make_unique<AverageFilter<3>>());

    // double angleError = target.convert(okapi::radian) - currAngle.convert(okapi::radian);
    // angleError = atan2(sin(angleError), cos(angleError));
    // tc.setTarget(angleError);
    // okapi::SettledUtil su = okapi::SettledUtilFactory::create(1, 0.2, 100_ms); // target Error, target derivative, settle time
    // bool disabled = false;

    // while (!su.isSettled(angleError * 180.0 / PI))
    // {
    //     angleError = target.convert(okapi::radian) - currAngle.convert(okapi::radian);
    //     angleError = atan2(sin(angleError), cos(angleError));
    //     tc.setTarget(0);
    //     double power = tc.step(-angleError);
    //     if (abs(power) < 0.5 && abs(angleError * 180.0/PI) < 0.4)
    //     {
    //         //chassis.stop();
    //         disabled = true;
    //         //chassis.rotate(power);
    //     }
    //     else
    //     {
    //         chassis.rotate(power);
    //     }
    //     pros::delay(10);      
    //     if (disabled) {
    //         break;
    //     }
    // }
    // chassis.stop();
}

void turnRelative(QAngle target)
{
    turnAbsolute((currAngle.convert(okapi::degree) + target.convert(okapi::degree)) * okapi::degree);
}

void driveApp() {
    appOn = true;
}

void waitUntilSettled() {
    while (!appController.isSettled()) {
        pros::delay(40);
    }
    appOn = false;
    chassis.stop();
}

void waitUntilSettled(int timeout) {
    std::uint32_t startTime = pros::millis();
    while (!appController.isSettled() || (pros::millis() - startTime) <= timeout) {
        pros::delay(40);
    }
    appOn = false;
    chassis.stop();
}

void runApp(void* p) {
    while (true) {
        if (appOn) {
            appController.loop();
        }
        pros::delay(10);
    }
}
} // namespace odometry