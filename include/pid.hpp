#if !defined(_PID_HPP)
#define _PID_HPP

#include "api.h"

class PID {
    public:
        double kP;
        double kI;
        double kD;
        PID (double kP, double kI, double kD, int target);
        double next(int sensor);
        void changeTarget(int target);
    protected:
        int dT;
        int lastTime;
        int target;
        int error;
        int lastError;
};

#endif // _PID_HPP
