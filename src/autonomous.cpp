#include "main.h"

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
    
    setAllMotorsBrakeMode(AbstractMotor::brakeMode::hold);
    //blueCloseAuto();
    //lcd::runAuton();
    // motionProfile.setTarget("E");
    // catapult::prepareLoad();
    // intake::forwardSpin();
    // descorer::moveTarget(240);
    // motionProfile.waitUntilSettled();
    // descorer::moveTarget(0);

    path::Line testus(
        {0_in, 0_in},
        {6_in, 48_in},
        200,
        20
    );


    path::Line test(
        {0_in, 0_in},
        {24_in, 0_in},
        200, // the resolution (how many T there are)
        20   // the lookahead T, and it's basically the maximum distance the robot will look ahead
    );

    path::Line test2(
        {24_in, 0_in},
        {24_in, 24_in},
        200,
        20
    );

    path::Line test3(
        {24_in, 24_in},
        {0_in, 24_in},
        200,
        20
    );

    path::Line test4(
        {0_in, 24_in},
        {0_in, 0_in},
        200,
        20
    );

    pathfollowing::AdaptivePurePursuit controller(
        std::make_unique<IterativePosPIDController>(0.2, 0.0, 0.0, 0.0, TimeUtilFactory::create(), std::make_unique<AverageFilter<5>>()),
        std::make_unique<IterativePosPIDController>(0.0075, 0.0, 0.0, 0.0, TimeUtilFactory::create(), std::make_unique<AverageFilter<5>>()),
        30, 0.0
    ); // the number before the Kf is the lookahead global, but it will use the path's lookahead by default

    controller.setPath(&testus);

    pros::Controller master(pros::E_CONTROLLER_MASTER);

    while (true)
    {
        std::string targAngle("Targ: " + std::to_string(controller.getAngleTarget().convert(okapi::degree)));
        //master.set_text(2, 0, targAngle.c_str());
        controller.loop();
        pros::delay(10);
    }

    // motionProfile.generatePath(
    //     {
    //         {odometry::currX, odometry::currY, odometry::currAngle},
    //         {24_in, 12_in, 0_deg}
    //     },
    //     "Test Path"
    // );

    // motionProfile.setTarget("Test Path");
}