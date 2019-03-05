#if !defined(_CATAPULT_HPP_)
#define _CATAPULT_HPP_

namespace catapult {
    
    const int LOAD_TARGET = 200;
    const int SLIP_CURRENT_DRAW = 600;

    extern okapi::MotorGroup catapult;
    extern okapi::Motor catapult1;
    extern okapi::Motor catapult2;

    void tare();
    void calibrate();
    void logCurrentDraw();
    void logAngle();
    void logState();

    typedef enum catapultState {
        shooting,
        lowering,
        lowered,
        movingBall,
        unmoving
    } tCatapultState;

    extern tCatapultState currState;
    
    tCatapultState updateState();
    void changeState(tCatapultState state);

    void load();
    void shoot();

    // change state to shoot and then run this to shoot, etc.
    void move(void* arg);
    void simpleMove();

    void prepareLoad();
}

#endif // _CATAPULT_HPP_
