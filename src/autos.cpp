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

    appController.setStraightGains(0.075, 0.0, 10);

    path::Bezier toFlag(
        {
            path::Point{-4_in, -1_in},
            path::Point{10_in, -1_in},
            path::Point{0_ft, -2_in},
            path::Point{39_in, -2_in}
        },
        200,
        200
    );
    appController.setPath(&toFlag);
    odometry::driveApp();
    odometry::waitUntilSettled();

    descorer::moveTarget(50);
    path::Bezier prePreScrape(
        {
            path::Point{3.4_ft, -2_in},
            path::Point{1.5_ft, -2_in},
            path::Point{2_ft, -0.5_ft},
            path::Point{0.5_ft, -0.5_ft}
        },
        200,
        200
    );
    appController.setPath(&prePreScrape);
    odometry::driveApp();
    motionProfile.generatePath(
        {
            {0_in, 0_in, 0_deg},
            {1.15_ft, 0_ft, 0_deg}
        },
        "Go to cap"
    );

    odometry::waitUntilSettled();
    odometry::turnAbsolute(45_deg);


    motionProfile.setTarget("Go to cap");
    descorer::moveTarget(185, 20);
    motionProfile.generatePath(
        {
            {0_in, 0_in, 0_deg},
            {0.5_ft, 0_ft, 0_deg}
        },
        "From Cap"
    );

    motionProfile.waitUntilSettled();
    descorer::waitUntilSettled();
    motionProfile.removePath("Go to cap");

    motionProfile.reverse();
    motionProfile.setTarget("From Cap");
    intake::forwardSpin(); // intake forward to intake

    motionProfile.waitUntilSettled();
    descorer::moveTarget(150);
    pros::delay(200);
    motionProfile.reverse();
    motionProfile.setTarget("From Cap");
    motionProfile.generatePath(
        {
            {0_in, 0_in, 0_deg},
            {0.75_ft, 0_ft, 0_deg}
        },
        "Go to Cap Again"
    );
    motionProfile.waitUntilSettled();
    motionProfile.removePath("From Cap");
    descorer::moveTarget(220);
    pros::delay(500);
    motionProfile.setTarget("Go to Cap Again");
    motionProfile.waitUntilSettled();
    
    descorer::moveTarget(50);
    odometry::turnAbsolute(45_deg);
    motionProfile.removePath("Go to Cap Again");
    pros::delay(700);
    catapult::shoot();
    pros::delay(500);
    intake::stop();
    catapult::changeState(catapult::lowering);
    descorer::moveTarget(50);
    path::Line finalBottomFlag(
        {1_ft, 1_ft},
        {3.8_ft, 2.9_ft},
        200,
        200
    );
    appController.setPath(&finalBottomFlag);
    chassis.setMaxVelocity(200);
    odometry::driveApp();
    odometry::waitUntilSettled();
    descorer::moveTarget(80);
    pros::delay(10000);
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