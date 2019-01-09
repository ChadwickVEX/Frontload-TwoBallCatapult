#ifndef _USER_CONFIG_HPP
#define _USER_CONFIG_HPP

#include "okapi/api.hpp"
#include "customAMPController.hpp"
#include <vector>

using namespace okapi;

const int RIGHT_BACK = 19;
const int LEFT_BACK = 20;
const int LEFT_FRONT = 17; // 6 and 8 r dead question mark
const int RIGHT_FRONT = 18;

const int CATAPULT_1 = 14; // left
const int CATAPULT_2 = 5; // right
const int INTAKE = 7;
const int DESCORER = 10;

const double DESCORER_RATIO = 5.0; 

const char CATAPULT_LIM = 'H';
const std::vector<char> RIGHT_ENC = {'A', 'B'};
const std::vector<char> LEFT_ENC = {'C', 'D'};

extern ChassisControllerIntegrated chassis;

const QLength ENC_WIDTH = 6_in;

const double ENC_TURN = 1.0 / ENC_WIDTH.convert(inch);
const double ENC_WHEEL = 2.75;

extern std::shared_ptr<ChassisControllerPID> chassisPID;

extern CustomAMPController motionProfile;

extern Motor mtrRB;
extern Motor mtrLB;
extern Motor mtrLF;
extern Motor mtrRF;

extern MotorGroup leftMotors;
extern MotorGroup rightMotors;

void setAllMotorsBrakeMode(AbstractMotor::brakeMode mode);

#endif
