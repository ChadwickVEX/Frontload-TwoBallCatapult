#include "main.h"

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	setAllMotorsBrakeMode(AbstractMotor::brakeMode::brake);
	const double threshold = 5.0;
	okapi::Logger *log = okapi::Logger::instance();

	visionControl::init();

	while (true) {
		int left = master.get_analog(ANALOG_LEFT_Y);
		int right = master.get_analog(ANALOG_RIGHT_Y);

		if (!visionControl::isTargeting()) { // if you're not targeting then user can control
			if (abs(left) < threshold && abs(right) < threshold) {
				setAllMotorsBrakeMode(AbstractMotor::brakeMode::brake);
				mtrRB.moveVelocity(0); // brake
				mtrRF.moveVelocity(0);
				mtrLB.moveVelocity(0);
				mtrLF.moveVelocity(0);
			} else {
				mtrRB.moveVoltage(12000 * ((double) right/127.0));
				mtrRF.moveVoltage(12000 * ((double) right/127.0));
				mtrLB.moveVoltage(12000 * ((double) left/127.0));
				mtrLF.moveVoltage(12000 * ((double) left/127.0));
			}
		}

		// catapult::simpleMove();
		catapult::updateState(); // move task is currently running
		intake::move();
		// catapult::logAngle();
		// catapult::logCurrentDraw();
		// catapult::logState();
		//log->debug("R: " + std::to_string(mtrRF.getPosition()) + ", " + "L: " + std::to_string(mtrLF.getPosition()));

		descorer::changeState();
		descorer::move();

		// TODO: Add if robot is disabled then set brakemode to coast so it's easy to move
		
		pros::delay(10);
	}
}
