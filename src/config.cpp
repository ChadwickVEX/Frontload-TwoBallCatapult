#include "main.h"

MotorGroup leftMotors({LEFT_BACK, LEFT_FRONT});
MotorGroup rightMotors({-RIGHT_BACK, -RIGHT_FRONT});

ChassisControllerIntegrated chassis = ChassisControllerFactory::create( // chassis controller integrated
    {LEFT_BACK, LEFT_FRONT},
    {-RIGHT_BACK, -RIGHT_FRONT},
    AbstractMotor::gearset::green,
    {4.125_in, 11.25_in});

// use for straight drives to correct for anomalies better than motion profiles will
// std::shared_ptr<ChassisControllerPID> chassisPID = std::make_shared<ChassisControllerPID>(
//     TimeUtilFactory::create(),
//     std::make_shared<SkidSteerModel>(std::make_shared<MotorGroup>(leftMotors), std::make_shared<MotorGroup>(rightMotors), 200),
//     std::make_unique<IterativePosPIDController>(0.0, 0.0, 0.0, 0.0, TimeUtilFactory::create(), std::make_unique<AverageFilter<5>>()), // distance
//     std::make_unique<IterativePosPIDController>(0.0, 0.0, 0.0, 0.0, TimeUtilFactory::create(), std::make_unique<AverageFilter<5>>()), // angle persist
//     std::make_unique<IterativePosPIDController>(0.0, 0.0, 0.0, 0.0, TimeUtilFactory::create(), std::make_unique<AverageFilter<5>>()), // turn
//     AbstractMotor::gearset::green,
//     chassis.getChassisScales()
// );
// TODO implement summing integral over a window
// REMEMBER TO chassisPID.startThread()

CustomAMPController motionProfile(
    TimeUtilFactory::create(),
    1.09, 4.0, 10.0, // maxvel, accel, max jerk
    chassis.getChassisModel(),
    chassis.getChassisScales(),
    AbstractMotor::gearset::green);

pathfollowing::AdaptivePurePursuit appController(
    std::make_unique<IterativePosPIDController>(0.09, 0.0, 1.0, 0.0, TimeUtilFactory::create(), std::make_unique<EmaFilter/*AverageFilter<5>*/>(0.4)),
    std::make_unique<IterativePosPIDController>(0.5, 0.0, 10.0, 0.0, TimeUtilFactory::create(), std::make_unique<EmaFilter/*AverageFilter<5>*/>(0.4)),
    200, 10.0); // turn was 0.6

Motor mtrRB(RIGHT_BACK, true, AbstractMotor::gearset::green);
Motor mtrLB(LEFT_BACK);
Motor mtrRF(RIGHT_FRONT, true, AbstractMotor::gearset::green);
Motor mtrLF(LEFT_FRONT);

void setAllMotorsBrakeMode(AbstractMotor::brakeMode mode)
{
    mtrRB.setBrakeMode(mode);
    mtrLB.setBrakeMode(mode);
    mtrRF.setBrakeMode(mode);
    mtrLF.setBrakeMode(mode);
}
