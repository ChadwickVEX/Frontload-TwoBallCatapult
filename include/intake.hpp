#ifndef _INTAKE_HPP_
#define _INTAKE_HPP_

namespace intake { 
    extern okapi::Motor intake;

    void move();

    void forwardSpin();

    void backwardSpin();

    void stop();
}

#endif