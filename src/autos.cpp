#include "main.h"
#include "config.hpp"

//blueclose
void blueClosePaths() {
    
}

// auton for blue side closer to flags
void blueCloseAuto() {
    descorer::init();
    catapult::changeState(catapult::lowering);
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
        {-4_in, 0_in},
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
    pros::delay(1000);
    //descorer::moveTarget(50);
    chassis.setMaxVelocity(100);
    odometry::turnAbsolute(90_deg); 
    chassis.setMaxVelocity(200);

    catapult::shoot();
    pros::delay(500);
    catapult::changeState(catapult::lowering);
    intake::stop();
    //descorer::moveTarget(100);
    // motionProfile.setTarget("Go To Flag");
    // motionProfile.waitUntilPathComplete();

    //pros::delay(400);

    appController.setStraightGains(0.075, 0.0, 0.0);

    path::Bezier toFlag(
        {
            path::Point{-4_in, 0_in},
            path::Point{10_in, -1_in},
            path::Point{0_ft, -2_in},
            path::Point{36_in, -2_in}
        },
        200,
        200
    );
    appController.setPath(&toFlag);
    odometry::driveApp();
    while (odometry::distanceToPoint(36_in, -4_in).convert(inch) > 6) {
        pros::delay(50);
    }
    descorer::moveTarget(100);
    odometry::waitUntilSettled();

    path::Bezier prePreScrape(
        {
            path::Point{36_in, -2_in},
            path::Point{1.5_ft, -2_in},
            path::Point{2_ft, 0.25_ft},
            path::Point{0.5_ft, 0.25_ft} // 0.5 ft was
        },
        200,
        200
    );
    appController.setPath(&prePreScrape);
    odometry::driveApp();
    pros::delay(500);
    descorer::moveTarget(50);
    motionProfile.generatePath(
        {
            {0_in, 0_in, 0_deg},
            {1.2_ft, 0_ft, 0_deg}
        },
        "Go to cap"
    );

    odometry::waitUntilSettled();
    pros::delay(1000);
    chassis.setMaxVelocity(130);
    odometry::turnAbsolute(45_deg);
    chassis.setMaxVelocity(200);

    motionProfile.setTarget("Go to cap");
    descorer::moveTarget(190, 20);
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
    // motionProfile.generatePath(
    //     {
    //         {0_in, 0_in, 0_deg},
    //         {0.4_ft, 0_ft, 0_deg}
    //     },
    //     "Go to Cap Again"
    // );
    // motionProfile.waitUntilSettled();
    // //pros::delay(200);
    // descorer::moveTarget(150);
    // pros::delay(400);
    // motionProfile.reverse();
    // motionProfile.setTarget("Go to Cap Again");
    // motionProfile.generatePath(
    //     {
    //         {0_in, 0_in, 0_deg},
    //         {0.6_ft, 0_ft, 0_deg}
    //     },
    //     "Go to Cap Again 2"
    // );

    // motionProfile.waitUntilSettled();
    //motionProfile.removePath("From Cap2");
        //descorer::moveTarget(210);
    //pros::delay(300);
    //motionProfile.setTarget("Go to Cap Again 2");
    motionProfile.waitUntilSettled();
    pros::delay(1000);
    descorer::moveTarget(50);

    chassis.setMaxVelocity(130);
    odometry::turnAbsolute(45_deg);
    chassis.setMaxVelocity(200);
    pros::delay(1300);
    
    //descorer::moveTarget(50);
    //motionProfile.removePath("Go to Cap Again");
    //pros::delay(200);
    catapult::shoot();
    pros::delay(300);
        intake::backwardSpin();
    catapult::changeState(catapult::unmoving);
    descorer::moveTarget(80);

    path::Line finalBottomFlag(
        {1_ft, 1_ft},
        {3.8_ft, 2.9_ft},
        200,
        200
    );
    appController.setPath(&finalBottomFlag);
    //catapult::changeState(catapult::lowering);
    chassis.setMaxVelocity(200);
    odometry::driveApp();
    odometry::waitUntilSettled();
    while(odometry::distanceToPoint(3.8_ft, 2.9_ft).convert(inch) > 12) {
        pros::delay(50);
    }
    intake::stop();
    descorer::moveTarget(100);
    pros::delay(1000);
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
    descorer::init();
    catapult::changeState(catapult::lowering);
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
        {4_in, -3_in},
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
    pros::delay(850);
    //descorer::moveTarget(50);
    chassis.setMaxVelocity(130);
    odometry::turnAbsolute(270_deg); 
    chassis.setMaxVelocity(200);

    catapult::shoot();
    pros::delay(500);
    catapult::changeState(catapult::lowering);
    intake::stop();
    //descorer::moveTarget(100);
    // motionProfile.setTarget("Go To Flag");
    // motionProfile.waitUntilPathComplete();

    //pros::delay(400);

    appController.setStraightGains(0.075, 0.0, 0.0);

    path::Bezier toFlag(
        {
            path::Point{4_in, -3_in},
            path::Point{-10_in, -3_in},
            path::Point{0_ft, -2_in},
            path::Point{-36_in, -2_in}
        },
        200,
        200
    );
    appController.setPath(&toFlag);
    odometry::driveApp();
    while (odometry::distanceToPoint(-36_in, -2_in).convert(inch) > 6) {
        pros::delay(50);
    }
    descorer::moveTarget(100);
    odometry::waitUntilSettled();

    path::Bezier prePreScrape(
        {
            path::Point{-36_in, -2.5_in},
            path::Point{-1.5_ft, -2.5_in},
            path::Point{-2_ft, 0_ft},
            path::Point{-0.5_ft, 0_ft} // 1 ft was
        },
        200,
        200
    );
    appController.setPath(&prePreScrape);
    odometry::driveApp();
    pros::delay(500);
    descorer::moveTarget(50);
    motionProfile.generatePath(
        {
            {0_in, 0_in, 0_deg},
            {-1.2_ft, 0_ft, 0_deg}
        },
        "Go to cap"
    );

    odometry::waitUntilSettled();

    pros::delay(800);

    chassis.setMaxVelocity(130);
    odometry::turnAbsolute(-45_deg);
    chassis.setMaxVelocity(200);

    motionProfile.setTarget("Go to cap");
    descorer::moveTarget(190, 20);
    motionProfile.generatePath(
        {
            {0_in, 0_in, 0_deg},
            {-0.5_ft, 0_ft, 0_deg}
        },
        "From Cap"
    );

    motionProfile.waitUntilSettled();
    descorer::waitUntilSettled();
    motionProfile.removePath("Go to cap");

    motionProfile.reverse();
    motionProfile.setTarget("From Cap");
    intake::forwardSpin(); // intake forward to intake
    // motionProfile.generatePath(
    //     {
    //         {0_in, 0_in, 0_deg},
    //         {0.4_ft, 0_ft, 0_deg}
    //     },
    //     "Go to Cap Again"
    // );
    // motionProfile.waitUntilSettled();
    // //pros::delay(200);
    // descorer::moveTarget(150);
    // pros::delay(400);
    // motionProfile.reverse();
    // motionProfile.setTarget("Go to Cap Again");
    // motionProfile.generatePath(
    //     {
    //         {0_in, 0_in, 0_deg},
    //         {0.6_ft, 0_ft, 0_deg}
    //     },
    //     "Go to Cap Again 2"
    // );

    // motionProfile.waitUntilSettled();
    //motionProfile.removePath("From Cap2");
        //descorer::moveTarget(210);
    //pros::delay(300);
    //motionProfile.setTarget("Go to Cap Again 2");
    motionProfile.waitUntilSettled();
    pros::delay(300);
    descorer::moveTarget(50);
    chassis.setMaxVelocity(130);
    odometry::turnAbsolute(-40_deg);
    chassis.setMaxVelocity(200);
    pros::delay(1500);
    
    //descorer::moveTarget(50);
    //motionProfile.removePath("Go to Cap Again");
    //pros::delay(200);
    catapult::shoot();
    pros::delay(300);
        intake::backwardSpin();
    catapult::changeState(catapult::unmoving);
    descorer::moveTarget(80);

    path::Line finalBottomFlag(
        {-1_ft, 1_ft},
        {-3.8_ft, 3.2_ft},
        200,
        200
    );
    appController.setPath(&finalBottomFlag);
    //catapult::changeState(catapult::lowering);
    chassis.setMaxVelocity(200);
    odometry::driveApp();
    odometry::waitUntilSettled();
    while(odometry::distanceToPoint(-3.8_ft, 2.9_ft).convert(inch) > 12) {
        pros::delay(50);
    }
    intake::stop();
    descorer::moveTarget(100);
    pros::delay(800);
    //escorer::moveTarget(0);
    //pros::delay(1000);
}

//redfar
void redFarPaths() {

}

void redFarAuto() {

}

void redFarAutoParkOnly() {

}





// REMEMBER TO REVERSE
void skills() {
    descorer::init();
    catapult::changeState(catapult::lowering);
    descorer::moveTarget(150);
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
        {-4_in, -2_in},
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
    pros::delay(850);
    //descorer::moveTarget(50);
    chassis.setMaxVelocity(130);
    odometry::turnAbsolute(90_deg); 
    chassis.setMaxVelocity(200);

    catapult::shoot();
    pros::delay(500);
    catapult::changeState(catapult::lowering);
    intake::stop();
    //descorer::moveTarget(100);
    // motionProfile.setTarget("Go To Flag");
    // motionProfile.waitUntilPathComplete();

    //pros::delay(400);

    appController.setStraightGains(0.075, 0.0, 0.0);

    path::Bezier toFlag(
        {
            path::Point{-4_in, -3_in}, // -2 v
            path::Point{10_in, -3_in},
            path::Point{-0_ft, -2_in},
            path::Point{36_in, -2_in}
        },
        200,
        200
    );
    appController.setPath(&toFlag);
    odometry::driveApp();
    while (odometry::distanceToPoint(36_in, -2_in).convert(inch) > 6) {
        pros::delay(50);
    }
    descorer::moveTarget(100);
    odometry::waitUntilSettled();

    path::Bezier prePreScrape(
        {
            path::Point{36_in, -2_in},
            path::Point{1.5_ft, -2_in},
            path::Point{2_ft, 0_ft},
            path::Point{0.5_ft, 0_ft} // 1 ft was
        },
        200,
        200
    );
    appController.setPath(&prePreScrape);
    odometry::driveApp();
    pros::delay(500);
    descorer::moveTarget(50);
    motionProfile.generatePath(
        {
            {0_in, 0_in, 0_deg},
            {1.2_ft, 0_ft, 0_deg}
        },
        "Go to cap"
    );

    odometry::waitUntilSettled();

    pros::delay(800);

    chassis.setMaxVelocity(130);
    odometry::turnAbsolute(45_deg);
    chassis.setMaxVelocity(200);

    motionProfile.setTarget("Go to cap");
    descorer::moveTarget(190, 20);
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
    // motionProfile.generatePath(
    //     {
    //         {0_in, 0_in, 0_deg},
    //         {0.4_ft, 0_ft, 0_deg}
    //     },
    //     "Go to Cap Again"
    // );
    // motionProfile.waitUntilSettled();
    // //pros::delay(200);
    // descorer::moveTarget(150);
    // pros::delay(400);
    // motionProfile.reverse();
    // motionProfile.setTarget("Go to Cap Again");
    // motionProfile.generatePath(
    //     {
    //         {0_in, 0_in, 0_deg},
    //         {0.6_ft, 0_ft, 0_deg}
    //     },
    //     "Go to Cap Again 2"
    // );

    // motionProfile.waitUntilSettled();
    //motionProfile.removePath("From Cap2");
        //descorer::moveTarget(210);
    //pros::delay(300);
    //motionProfile.setTarget("Go to Cap Again 2");
    motionProfile.waitUntilSettled();
    pros::delay(300);
    descorer::moveTarget(50);
    chassis.setMaxVelocity(130);
    odometry::turnAbsolute(40_deg);
    chassis.setMaxVelocity(200);
    pros::delay(1500);
    
    //descorer::moveTarget(50);
    //motionProfile.removePath("Go to Cap Again");
    //pros::delay(200);
    catapult::shoot();
    pros::delay(300);
        intake::backwardSpin();
    catapult::changeState(catapult::unmoving);
    descorer::moveTarget(80);

    path::Line finalBottomFlag(
        {1_ft, 1_ft},
        {3.8_ft, 3.2_ft},
        200,
        200
    );
    appController.setPath(&finalBottomFlag);
    //catapult::changeState(catapult::lowering);
    chassis.setMaxVelocity(200);
    odometry::driveApp();
    odometry::waitUntilSettled();
    while(odometry::distanceToPoint(3.8_ft, 3.2_ft).convert(inch) > 12) {
        pros::delay(50);
    }
    intake::stop();
    descorer::moveTarget(100);


    path::Line platformLineup(
        {3.8_ft, 3.2_ft},
        {1_ft, 0.5_ft},
        200,
        200
    );

    appController.setPath(&platformLineup);
    odometry::driveApp();
    odometry::waitUntilSettled();

    path::Line platformABitForward(
        {1_ft, 0.5_ft},
        {-2.25_ft, 0.5_ft},
        200,
        200
    );

    appController.setPath(&platformLineup);
    odometry::driveApp();
    odometry::waitUntilSettled();

    appController.setPath(&platformABitForward);
    odometry::driveApp();
    odometry::waitUntilSettled();

    pros::delay(1000);

    odometry::turnAbsolute(0_deg);

    intake::forwardSpin();

    chassis.moveDistance(6_ft);
}