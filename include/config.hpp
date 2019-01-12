#ifndef _USER_CONFIG_HPP
#define _USER_CONFIG_HPP

#include "okapi/api.hpp"
#include "customAMPController.hpp"
#include <vector>

using namespace okapi;

const int RIGHT_BACK = 2;
const int LEFT_BACK = 1;
const int LEFT_FRONT = 19; // 6 and 8 r dead question mark
const int RIGHT_FRONT = 20;

const int CATAPULT_1 = 9; // left
const int CATAPULT_2 = 18; // right from the front
const int INTAKE = 10;
const int DESCORER = 3;

const double DESCORER_RATIO = 1.0; 

const char CATAPULT_LIM = 'H';
const std::vector<char> LEFT_ENC = {'A', 'B'};
const std::vector<char> RIGHT_ENC = {'C', 'D'};

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
