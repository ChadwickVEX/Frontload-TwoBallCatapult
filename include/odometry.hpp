#pragma once

#include "api.h"
#include "okapi/api.hpp"
#include <tuple>
#include "config.hpp"

namespace odometry
{
using namespace okapi;

extern QLength currX;
extern QLength currY;
extern QAngle currAngle;

void init();

void calculate();

QLength distanceToPoint(QLength x, QLength y);
QAngle angleToPoint(QLength x, QLength y);

std::tuple<QLength, QAngle> distanceAndAngleToPoint(QLength x, QLength y);

QLength distanceToPoint(QLength x, QLength y);

void run(void *p);

void turnAbsolute(QAngle angle);

void turnRelative(QAngle angle);

void driveApp();

void waitUntilSettled();

void waitUntilSettled(int time);

void runApp(void *p);

} // namespace odometry
