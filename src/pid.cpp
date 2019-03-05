#include "main.h"

PID::PID(double kP, double kI, double kD, int target) : kP(kP), kI(kI), kD(kD), oldTime(pros::millis()), desiredValue(target), error(target)
{}

double PID::limit(double val, double min = -1.0, double max = 1){//caps a value
	if(val>max){
		return max;
	}
	if(val<min){
		return min;
	}
	return val;
}

/**
 * Next PID step.
 * Constrained between [-1, 1]
 */
double PID::next(int reading)
{
    //calculate delta time since last call
    this->timeChange = pros::millis()-this->oldTime;
    this->oldTime = pros::millis();
    if(this->timeChange>100||this->timeChange == 0){
        this->timeChange = 50;
    }
    //calculate error
    this->error = this->desiredValue-(this->reverseSensor?-1:1)*reading;
    //set P value
    this->pVal = this->error;

    //subtract oldest value from I
    this->iVal -= this->oldErrorArr[this->writeCounterI];

    //add newest value to I
    if(fabs(this->error)<this->maxErrorI){
        this->iVal += this->error*this->timeChange;
        this->oldErrorArr[this->writeCounterI] = this->error*this->timeChange;
    }

    //calculate derivative
    this->dVal = this->oldSensorValue-(this->reverseSensor?-1:1)*reading;
    //avoid stupid errors when changing setpoint
    if(fabs(this->dVal)>1000){
        this->dVal = 0;
    }
    this->dAverage+=this->dVal;
    this->dAverage-=this->oldDerivatives[this->writeCounterD];
    this->oldDerivatives[this->writeCounterD] = this->dVal;

    //set oldSensorValue
    this->oldSensorValue = (this->reverseSensor?-1:1)*reading;

    //increment writeCounterD in circular array
    this->writeCounterD++;
    this->writeCounterD %= (sizeof(this->oldDerivatives)/sizeof(this->oldDerivatives[0]));

    //set I to 0 if within acceptable range
    if(fabs(this->error)<this->acceptableRange){
        this->oldErrorArr = {0};
        this->iVal = 0;
    }

    //set old error in circular array
    this->writeCounterI++;
    this->writeCounterI %= (sizeof(this->oldErrorArr)/sizeof(this->oldErrorArr[0]));

    //return motor Value
    return this->pVal*this->kP +
    limit(this->iVal*this->kI,-50,50) +
    this->dAverage*this->kD/sizeof(this->oldDerivatives)/sizeof(this->oldDerivatives[0])/(float)this->timeChange;
}

void PID::changeTarget(int target)
{
    this->desiredValue = target;
}
