#include "main.h"

void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	// Logger::initialize(
	// 	TimeUtilFactory::create().getTimer(),
	// 	"/ser/sout", // output to the PROS terminal over standard out
	// 	Logger::LogLevel::off /* // most verbose log level is debug*/
	// );

	lcd::initButtons();

    motionProfile.startThread();

	//blueClosePaths();

	odometry::init();

    pros::Task odometryTask(odometry::run, nullptr, TASK_PRIORITY_DEFAULT + 1, TASK_STACK_DEPTH_DEFAULT, "Odometry");
    pros::Task appTask(odometry::runApp, nullptr, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Adaptive Pure Pursuit");

	pros::Task catapultTask(catapult::move, (void*)1, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Catapult Move");
	pros::Task pathTask(lcd::generatePaths, nullptr, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Path Generation");

	//pros::lcd::initialize();

	//pros::lcd::print(0, "Running init");

	catapult::tare(); // tare catapult at 0 pos being fired position
	//descorer::init();
	// pros::lcd::register_btn1_cb(lcd::pickMiddle); // TODO use PROS callbacks instead of my own polling
	// pros::lcd::register_btn0_cb(lcd::pickLeft);
	// pros::lcd::register_btn2_cb(lcd::pickRight);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	//pros::lcd::print(0, "Running competition_initialize()");
	// if (pros::competition::is_disabled()) {
	// 	descorer::compInit();
	// }
	//odometry::init();
	//catapult::tare();
	//descorer::init();
	//catapult::changeState(catapult::lowering);
}
