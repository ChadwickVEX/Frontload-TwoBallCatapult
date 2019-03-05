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
	    double acceptableRange = 0;
	    double maxErrorI = 0;
	    int sensorPort = 0;
	    bool reverseSensor = 0;
	    double error = 0;
	    double desiredValue = 0;
	    double pVal = 0;
	    double iVal = 0;
	    double dVal = 0;
	    double dAverage = 0;
	    std::array<int, 100> oldErrorArr{0};
	    std::array<double, 5> oldDerivatives{0.0};
	    int oldTime = 0;
	    double oldSensorValue = 0;
	    double timeChange = 0;
	    int writeCounterI = 0;
	    int writeCounterD = 0;

    private:
        double limit(double val, double min, double max);

};

#endif // _PID_HPP
