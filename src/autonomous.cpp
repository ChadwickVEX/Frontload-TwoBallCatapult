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
void autonomous()
{

    setAllMotorsBrakeMode(AbstractMotor::brakeMode::hold);


    //skills();
    //redCloseAuto();
    //lcd::runAuton();
    skills();

    //chassis.setMaxVelocity(100);
    //chassis.moveDistance(4_ft); // use to test encoders
    //chassis.moveDistance(-4_ft);
    //chassis.moveDistance(4_ft);
    //chassis.moveDistance(-4_ft); // expected: 2000 ticks both directions

    //chassis.turnAngle(90_deg);
    //odometry::currAngle = 30_deg;
    //odometry::turnAbsolute(90_deg);
    //chassis.turnAngle(62.4_deg);

    // odometry::currX = 3.8_ft;
    // odometry::currY = 2.9_ft;

    // path::Bezier theFinalCap(
    //     {
    //         path::Point{3.8_ft, 2.9_ft},
    //         path::Point{1.3_ft, 1.3_ft},
    //         path::Point{2_ft, -3_ft},
    //         path::Point{2_ft, 6.5_ft},
    //         path::Point{2_ft, 6_ft}
    //     },
    //     400,
    //     100
    // );

    // appController.setPath(&theFinalCap);
    // odometry::driveApp();
    // odometry::waitUntilSettled();


    // appController.setStraightGains(0.07, 0.0, 1.0);

    // path::Bezier boi(
    //     {
    //         path::Point{0_in, 0_in},
    //         path::Point{0_in, 2_ft},
    //         path::Point{2_ft, 2_ft},
    //         path::Point{2_ft, 6_ft}
    //     },
    //     200,
    //     200
    // );

    // appController.setPath(&boi);
    // odometry::driveApp();
    // odometry::waitUntilSettled();
    // pros::delay(800);

    // path::Bezier bababoi(
    //     {
    //         path::Point{2_in, 6_in},
    //         path::Point{2_in, 2_ft},
    //         path::Point{0_ft, 2_ft},
    //         path::Point{0_ft, 0_ft}
    //     },
    //     200,
    //     200
    // );

    // appController.setPath(&bababoi);
    // odometry::driveApp();
    // odometry::waitUntilSettled();
    // pros::delay(200);


    // intake::forwardSpin();

    // path::Line forwardToBall(
    //     {0_in, 0_in},
    //     {0_in, 3_ft},
    //     200,
    //     200
    // );

    // appController.setPath(&forwardToBall);

    // odometry::driveApp();

    // odometry::waitUntilSettled();
    // pros::delay(200);

    // path::Line backwardFromBall(
    //     {0_in, 3_ft},
    //     {0_in, 0_in},
    //     200,
    //     200
    // );

    // appController.setPath(&backwardFromBall);

    // odometry::driveApp();
    // odometry::waitUntilSettled();

}

void appcSquare()
{
    path::Line testus(
        {0_in, 0_in},
        {0_in, 60_in},
        200,
        200);

    path::Line testusProcedural(
        {0_in, 60_in},
        {-80_in, 60_in},
        200,
        200);

    path::Line testusProceduralProcedural(
        {-80_in, 60_in},
        {-80_in, 0_in},
        200,
        200);

    path::Line testusProceduralProceduralProcedural(
        {-80_in, 0_in},
        {0_in, 0_in},
        200,
        200);

    path::Line test(
        {0_in, 0_in},
        {0_in, 65_in},
        200, // the resolution (how many T there are)
        50   // the lookahead T, and it's basically the maximum distance the robot will look ahead
    );

    path::Line test2(
        {0_in, 65_in},
        {-7_ft, 5.5_ft},
        200,
        50);

    path::Line test3(
        {-7_ft, 60_in},
        {-7_ft, 0_in},
        200,
        50);

    path::Line test4(
        {36_in, 0_in},
        {0_in, 0_in},
        200,
        50);

    path::PathGroup testGroup(
        {
            test,
            test2 //,
            //test3
        },
        400,
        10);

    pathfollowing::AdaptivePurePursuit controller(
        std::make_unique<IterativePosPIDController>(0.2, 0.0, 60.0, 0.0, TimeUtilFactory::create(), std::make_unique<AverageFilter<5>>()),
        std::make_unique<IterativePosPIDController>(0.6, 0.0, 20.0, 0.0, TimeUtilFactory::create(), std::make_unique<AverageFilter<5>>()),
        10, 10.0); // the number before the Kf is the lookahead global, but it will use the path's lookahead by default

    controller.setPath(&testus);

    pros::Controller master(pros::E_CONTROLLER_MASTER);

    while (!controller.isSettled())
    {
        //std::string targAngle("Targ: " + std::to_string(controller.getAngleTarget().convert(okapi::degree)));
        //master.set_text(2, 0, targAngle.c_str());
        controller.loop();
        pros::delay(10);
    }

    controller.setPath(&testusProcedural);
    while (!controller.isSettled())
    {
        controller.loop();
        pros::delay(10);
    }
    controller.setPath(&testusProceduralProcedural);
    while (!controller.isSettled())
    {
        controller.loop();
        pros::delay(10);
    }
    controller.setPath(&testusProceduralProceduralProcedural);
    while (!controller.isSettled())
    {
        controller.loop();
        pros::delay(10);
    }
    chassis.stop();
}