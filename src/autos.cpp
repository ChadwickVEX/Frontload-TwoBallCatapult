#include "main.h"
#include "config.hpp"

//blueclose
void blueClosePaths() {
}

// auton for blue side closer to flags
void blueCloseAuto() {
    descorer::init();
    descorer::moveTarget(50);
    intake::forwardSpin();
    path::Line toBall(
        {0_in, 0_in},
        {0_in, 3_ft},
        200,
        200
    );
    appController.setPath(&toBall);
    odometry::driveApp();
    odometry::waitUntilSettled();
    pros::delay(700);

    path::Line backToSquare(
        {0_in, 3_ft},
        {-4_in, -3_in},
        200,
        200
    );

    appController.setPath(&backToSquare);
    odometry::driveApp();
    // motionProfile.generatePath(
    //     {
    //         Point{0_in, 1_in, 90_deg},
    //         Point{1.5_ft, 0_in, 90_deg}
    //     },
    //     "Go To Flag"
    // );

    odometry::waitUntilSettled();
    descorer::moveTarget(100);
    odometry::turnAbsolute(90_deg);
    catapult::shoot();
    pros::delay(500);
    catapult::changeState(catapult::lowering);
    intake::stop();
    descorer::moveTarget(100);
    // motionProfile.setTarget("Go To Flag");
    // motionProfile.waitUntilPathComplete();

    pros::delay(400);
    path::Bezier toFlag(
        {
            path::Point{-4_in, -1_in},
            path::Point{10_in, -1_in},
            path::Point{0_ft, -4_in},
            path::Point{40_in, -4_in}
        },
        200,
        200
    );
    appController.setPath(&toFlag);
    odometry::driveApp();
    odometry::waitUntilSettled();

    descorer::moveTarget(50);

    // path::Line prePreScrape(
    //     {2_ft, -4_in},
    //     {0.5_ft, 0.5_ft},
    //     200,
    //     200
    // );
    path::Bezier prePreScrape(
        {
            path::Point{2_ft, -4_in},
            path::Point{1_ft, -4_in},
            path::Point{1_ft, 0.5_ft},
            path::Point{0.5_ft, 0.5_ft}
        },
        200,
        200
    );
    appController.setPath(&prePreScrape);
    odometry::driveApp();
    odometry::waitUntilSettled();
    odometry::turnAbsolute(45_deg);

    chassis.setMaxVelocity(70);
    chassis.moveDistanceAsync(1.8_ft); // drive to the cap
    pros::delay(400);
    descorer::moveTarget(185, 20);
    chassis.waitUntilSettled();
    intake::forwardSpin(); // intake forward to intake
    chassis.setMaxVelocity(100);
    chassis.moveDistance(-1_ft);
    descorer::moveTarget(150);
    chassis.moveDistance(-0.5_ft);
    descorer::moveTarget(210);
    pros::delay(700);
    chassis.setMaxVelocity(100);
    chassis.moveDistance(1.25_ft);
    chassis.setMaxVelocity(100);
    chassis.moveDistance(-0.25_ft);
    odometry::turnAbsolute(45_deg);
    catapult::shoot();
    pros::delay(500);
    intake::stop();
    catapult::changeState(catapult::lowering);
    descorer::moveTarget(50);
    path::Line finalBottomFlag(
        {1_ft, 1_ft},
        {3.75_ft, 3.3_ft},
        200,
        200
    );
    appController.setPath(&finalBottomFlag);
    chassis.setMaxVelocity(200);
    odometry::driveApp();
    odometry::waitUntilSettled();
    descorer::moveTarget(80);
    pros::delay(10000);
    // path::Line bottomFlag(
    //     {0_in, -1_in},
    //     {3_ft, -1_in},
    //     200,
    //     200
    // );
    //appController.setPath(&bottomFlag);
    //odometry::driveApp();
    //odometry::waitUntilSettled();
}

//bluefar
void blueFarPaths() {

}

void blueFarAuto() {

}

//redclose
void redClosePaths() {

}

void redCloseAuto() {

}

//redfar
void redFarPaths() {

}

void redFarAuto() {

}

void redFarAutoParkOnly() {

}