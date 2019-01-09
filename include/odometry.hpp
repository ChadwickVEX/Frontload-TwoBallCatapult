#if !defined(_ODOMETRY_HPP_)
#define _ODOMETRY_HPP_

#include "okapi/api.hpp"
#include <tuple>

namespace odometry {
    using namespace okapi;

    QLength currX;
    QLength currY;
    QAngle currAngle;

    void init();

    void calculate();

    QLength distanceToPoint(QLength x, QLength y);
    QAngle angleToPoint(QLength x, QLength y);

    std::tuple<QLength, QAngle> distanceAndAngleToPoint(QLength x, QLength y);

    void run(void *p);
}

#endif // _ODOMETRY_HPP_
