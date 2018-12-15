#if !defined(_DESCORER_HPP_)
#define _DESCORER_HPP_

#include "okapi/api.hpp"

namespace descorer {
    extern okapi::Motor descorer;

    void init();

    void move();

    void changeState();

    void moveTarget(int target);

    void moveTarget(int target, int speed);

    void waitUntilSettled();
}

#endif // _DESCORER_HPP_
