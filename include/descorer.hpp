#if !defined(_DESCORER_HPP_)
#define _DESCORER_HPP_

#include "okapi/api.hpp"

namespace descorer {
    extern okapi::Motor descorer;
    extern bool isCalibrating;

    void init();

    void compInit();

    void move();

    void changeState();

    void changeState(int count);

    void moveTarget(int target);

    void moveTarget(int target, int speed);

    void waitUntilSettled();

    void calibrate(void* p);
}

#endif // _DESCORER_HPP_
