#include "main.h"
#include "config.hpp"

//blueclose
void blueClosePaths() {
    motionProfile.removePath("RdriveToCap 1 Red");
    motionProfile.removePath("RdriveToCap 1 Blue");
    motionProfile.generatePath({
		Point{0_ft, 0_ft, 0_deg},
		Point{3.8_ft, 0_ft, 0_deg}}, // was 3.7
		"BlueClose1"
	);
}

// auton for blue side closer to flags
void blueCloseAuto() {
    catapult::changeState(catapult::lowering);
    intake::forwardSpin();
    motionProfile.setTarget("BlueClose1"); // drive forward to the first cap
    motionProfile.generatePath({
        Point{0_ft, 0_ft, 0_deg},
        //Point{1.75_ft, -1 * 0.5_ft, 45_deg},
        Point{3.3_ft, -1 * 0.5_ft, 0_deg} // was 3.2
        },
        "RBlueClose2"
    );
    //motionProfile.waitUntilPathComplete();
    //intake::forwardSpin();
    motionProfile.waitUntilSettled(); // wait for finish
    //intake::forwardSpin();
    motionProfile.removePath("BlueClose1");
    //pros::delay(400);
    motionProfile.reverse(); // reverse the next path
    motionProfile.setTarget("RBlueClose2");
    motionProfile.generatePath({
        Point{0_ft, 0_ft, 0_deg},
        Point{3.1_ft, 0.4_ft, 0_deg} // was 3.3, 0.5 was 2.8
        /*,Point{4_ft,-0.6_ft, 0_deg}*/},
        "RBlueClose3"
    );
    motionProfile.waitUntilSettled();
    motionProfile.forward(); // make sure direction is changed to forward
    motionProfile.removePath("RBlueClose2");
    chassis.setMaxVelocity(150);
    chassis.turnAngle(-90_deg); // turn to flags was 87
    //chassis.waitUntilSettled();
    chassis.setMaxVelocity(200);
    catapult::changeState(catapult::shooting); // shoot
    catapult::logState();
    pros::delay(500);
    catapult::changeState(catapult::lowering);
    catapult::logState();
    //intake::stop();
    //chassis.turnAngle(0_deg); // turn slightly to hit flag TODO use a path
    //chassis.moveDistance(-2.5_ft); // hit the low flag
    //chassis.turnAngle(1_deg);
    descorer::moveTarget(60 * 5);
    motionProfile.reverse();
    motionProfile.setTarget("RBlueClose3");
    motionProfile.generatePath({
        Point{0_ft, 0_ft, 0_deg},
        Point{2.8_ft, -1 * 4.7_ft, 0_deg}//, // was 1, 1 was 2.5, -4.7
        /*Point{2_ft, 1 * 3.8_ft, 90_deg}*/}, // 1, 3.5 was 3.5
        "BlueClose4"
    );
    motionProfile.waitUntilSettled();
    motionProfile.removePath("RBlueClose3");
    motionProfile.forward();0;
    motionProfile.setTarget("BlueClose4"); // move to other cap
    descorer::moveTarget(0);
    intake::stop();
    pros::delay(100);
    intake::backwardSpin(); // prepare to flip other cap
    //pros::delay(1500);
    //intake::stop();
    motionProfile.waitUntilSettled();
    motionProfile.removePath("BlueClose4");
    //chassis.moveDistance(1.375_ft); // drive forward a bit more to flip
    // chassis.setMaxVelocity(130);
    // chassis.turnAngle(-59_deg); // turn to platform
    // chassis.setMaxVelocity(200);
    intake::stop();
    chassis.moveDistance(2_ft); // park


    //catapult::changeState(catapult::shooting); // shoot catapult {MAKE SURE MODIFICATIONS TO CONTROL TASK WORK}
    // turn to the right 90 degrees
    // drive forward and flip cap
    // then drive to park --> either use path or just go forward, turn right, and drive forward again
}

//bluefar
void blueFarPaths() {
    motionProfile.removePath("BlueClose1");
    motionProfile.removePath("RdriveToCap 1 Red");
    motionProfile.generatePath(
        {
            Point{0_in, 0_in, 0_deg},
            /*Point{44_in, -22_in, 0_deg},*/
            Point{40_in, 0_ft, 0_deg}
        },
        "driveToCap 1 Blue"
    );
}

void blueFarAuto() {
    intake::forwardSpin();
    motionProfile.setTarget("driveToCap 1 Blue");
    motionProfile.generatePath(
        {
            Point{0_in, 0_in, 0_deg},
            /*Point{44_in, -22_in, 0_deg},*/
            Point{0.2_ft, 0_in, 0_deg}
        },
        "Rdrive away"
    );
    motionProfile.waitUntilSettled();
    motionProfile.reverse();
    motionProfile.setTarget("Rdrive away");
    motionProfile.waitUntilSettled();
    chassis.setMaxVelocity(130);
    chassis.turnAngleAsync(90);
    chassis.waitUntilSettled();
    intake::stop();
    chassis.setMaxVelocity(200);
    chassis.moveDistance(4.5_ft);
}

void blueFarAutoParkOnly() {
    intake::forwardSpin();
    motionProfile.setTarget("driveToCap 1 Blue");
    motionProfile.generatePath(
        {
            Point{0_in, 0_in, 0_deg},
            /*Point{44_in, -22_in, 0_deg},*/
            Point{1_ft, 10_in, 0_deg}
        },
        "Rdrive away"
    );
    motionProfile.waitUntilSettled();
    motionProfile.reverse();
    motionProfile.setTarget("RDrive away");
    chassis.setMaxVelocity(130);
    chassis.turnAngle(90);
    chassis.setMaxVelocity(200);
    chassis.moveDistance(4.5_ft);
}

//redclose
void redClosePaths() {

    blueClosePaths();

    // motionProfile.generatePath({
	// 	Point{0_ft, 0_ft, 0_deg},
	// 	Point{3.6_ft, 0_ft, 0_deg}}, // was 2.5
	// 	"RedClose1"
	// ); // same as blueClose1 so maybe dont generate this too

    // motionProfile.generatePath({
    //     Point{0_ft, 0_ft, 0_deg},
    //     //Point{1.75_ft, -1 * 0.5_ft, 45_deg},
    //     Point{3.45_ft, 1.5_ft, 0_deg} // 1.5, was 3.15 was 1 was 3.35
    //     },
    //     "RRedClose2"
    // );

    // motionProfile.generatePath({
    //     Point{0_ft, 0_ft, 0_deg},
    //     Point{1_ft, 1_ft, -1 * 90_deg},
    //     Point{1_ft, 3_ft, -1 * 90_deg}},
    //     "RedClose3"
    // );
}

void redCloseAuto() {
    catapult::changeState(catapult::lowering);
    intake::forwardSpin();
    motionProfile.setTarget("BlueClose1"); // drive forward to the first cap
    motionProfile.generatePath({
        Point{0_ft, 0_ft, 0_deg},
        //Point{1.75_ft, -1 * 0.5_ft, 45_deg},
        Point{3.3_ft, 1 * 0.5_ft, 0_deg} // was 3.2
        },
        "RBlueClose2"
    );
    //motionProfile.waitUntilPathComplete();
    //intake::forwardSpin();
    motionProfile.waitUntilSettled(); // wait for finish
    //intake::forwardSpin();
    motionProfile.removePath("BlueClose1");
    //pros::delay(400);
    motionProfile.reverse(); // reverse the next path
    motionProfile.setTarget("RBlueClose2");
    motionProfile.generatePath({
        Point{0_ft, 0_ft, 0_deg},
        Point{3.1_ft, -0.4_ft, 0_deg} // was 3.3, 0.5 was 2.8
        /*,Point{4_ft,-0.6_ft, 0_deg}*/},
        "RBlueClose3"
    );
    motionProfile.waitUntilSettled();
    motionProfile.forward(); // make sure direction is changed to forward
    motionProfile.removePath("RBlueClose2");
    chassis.setMaxVelocity(100);
    chassis.turnAngle(90_deg); // turn to flags was 87
    //chassis.waitUntilSettled();
    chassis.setMaxVelocity(200);
    catapult::changeState(catapult::shooting); // shoot
    catapult::logState();
    pros::delay(500);
    catapult::changeState(catapult::lowering);
    catapult::logState();
    //intake::stop();
    //chassis.turnAngle(0_deg); // turn slightly to hit flag TODO use a path
    //chassis.moveDistance(-2.5_ft); // hit the low flag
    //chassis.turnAngle(1_deg);
    descorer::moveTarget(60 * 5);
    motionProfile.reverse();
    motionProfile.setTarget("RBlueClose3");
    motionProfile.generatePath({
        Point{0_ft, 0_ft, 0_deg},
        Point{2.8_ft, 1 * 4.25_ft, 0_deg}//, // was 1, 1 was 2.5, -4.7
        /*Point{2_ft, 1 * 3.8_ft, 90_deg}*/}, // 1, 3.5 was 3.5
        "BlueClose4"
    );
    motionProfile.waitUntilSettled();
    motionProfile.removePath("RBlueClose3");
    motionProfile.forward();0;
    motionProfile.setTarget("BlueClose4"); // move to other cap
    descorer::moveTarget(0);
    intake::stop();
    pros::delay(100);
    intake::backwardSpin(); // prepare to flip other cap
    //pros::delay(1500);
    //intake::stop();
    motionProfile.waitUntilSettled();
    motionProfile.removePath("BlueClose4");
    //chassis.moveDistance(1.375_ft); // drive forward a bit more to flip
    // chassis.setMaxVelocity(130);
    // chassis.turnAngle(-59_deg); // turn to platform
    // chassis.setMaxVelocity(200);
    intake::stop();
    chassis.moveDistance(2.2_ft); // park
}

//redfar
void redFarPaths() {
    motionProfile.removePath("BlueClose1");
    motionProfile.generatePath(
        {
            Point{0_in, 0_in, 0_deg},
            /*Point{44_in, -22_in, 0_deg},*/
            Point{40_in, 0_ft, 0_deg}
        },
        "driveToCap 1 Blue"
    );

    //motionProfile.removePath("RdriveToCap 1 Blue");
    // motionProfile.generatePath(
    //     {
    //         Point{0_in, 0_in, 0_deg},
    //         /*Point{44_in, -22_in, 0_deg},*/
    //         Point{30_in, 31_in, 0_deg}
    //     },
    //     "RdriveToCap 1 Red"
    // );
}

void redFarAuto() {
    motionProfile.reverse();
    motionProfile.setTarget("RdriveToCap 1 Red");
    motionProfile.generatePath(
        {
            Point{0_in, 0_in, 0_deg},
            /*Point{44_in, -22_in, 0_deg},*/
            Point{29_in, -32_in, 0_deg}
        },
        "drive to pole"
    );
    motionProfile.waitUntilSettled();
    motionProfile.removePath("RdriveToCap 1 Red");
    motionProfile.forward();
    chassis.setMaxVelocity(25);
    chassis.moveDistanceAsync(-0.5_ft);
    pros::delay(700);
    descorer::moveTarget(60 * 5, 60);
    pros::delay(300);
    chassis.waitUntilSettled();
    chassis.setMaxVelocity(80);
    motionProfile.setTarget("drive to pole");
    motionProfile.waitUntilSettled();
    motionProfile.removePath("drive to pole");
    //chassis.moveDistance(1_ft);
    chassis.turnAngle(-92_deg);
    chassis.setMaxVelocity(65);
    descorer::moveTarget(155 * 5, 180);
    chassis.moveDistance(10_in);
    pros::delay(2700);
    //descorer::waitUntilSettled();
    chassis.setMaxVelocity(75);
    descorer::moveTarget(0);
    chassis.moveDistance(-1.3_ft);
    chassis.turnAngle(35_deg);
    chassis.moveDistance(1.1_ft);
    catapult::changeState(catapult::shooting);
    pros::delay(1000);
    catapult::changeState(catapult::lowering);

}

void redFarAutoParkOnly() {
    intake::forwardSpin();
    motionProfile.setTarget("driveToCap 1 Blue");
    motionProfile.generatePath(
        {
            Point{0_in, 0_in, 0_deg},
            /*Point{44_in, -22_in, 0_deg},*/
            Point{0.2_ft, 0_in, 0_deg}
        },
        "Rdrive away"
    );
    motionProfile.waitUntilSettled();
    pros::delay(300);
    motionProfile.reverse();
    motionProfile.setTarget("Rdrive away");
    motionProfile.waitUntilSettled();
    chassis.setMaxVelocity(130);
    chassis.turnAngleAsync(-200);
    chassis.waitUntilSettled();
    intake::stop();
    chassis.setMaxVelocity(200);
    chassis.moveDistance(3.8_ft);

}