#include "odometry.hpp"
#include "config.hpp"

namespace odometry {
    ADIEncoder rightEnc(RIGHT_ENC.front(), RIGHT_ENC.back(), false);
    ADIEncoder leftEnc(LEFT_ENC.front(), LEFT_ENC.back());

    double rEncLast;
    double lEncLast;

    void init() {
        currX = 0_ft;
        currY = 0_ft;   
        currAngle = 0_deg; 

        rEncLast = rightEnc.get() * ENC_WHEEL * PI / 360.0;
        lEncLast = leftEnc.get() * ENC_WHEEL * PI / 360.0;
    }

    /**
     * Iterate
     */
    void calculate() {
        double dX = 0.0;
        double dY = 0.0;
        double dTheta = 0.0;
        double chordTheta = 0.0;

        double rCurrEnc = rightEnc.get() * ENC_WHEEL * PI / 360.0;
        double lCurrEnc = leftEnc.get() * ENC_WHEEL * PI / 360.0;

        double rDEnc = rCurrEnc - rEncLast;
        double lDEnc = lCurrEnc - lEncLast;

        dTheta = (rDEnc - lDEnc) * ENC_TURN * PI / 180.0;

        double avgArc = (rDEnc + lDEnc) / 2.0;
        avgArc *= 2.0 * cos(dTheta / 2.0) / dTheta;
        chordTheta = (currAngle.convert(degree) + (dTheta * 180.0 / PI)) / 2.0 * PI / 180.0;

        dX = (avgArc * cos(chordTheta))/* + (dMiddleArc * sin(chordTheta))*/;
        dY = (avgArc * sin(chordTheta))/* - (dMiddleArc * cos(chordTheta))*/;

        currAngle += dTheta * 180.0/PI * degree;

        currX += dX * inch;
        currY += dY * inch;

        rEncLast = rCurrEnc;
        lEncLast = lCurrEnc;        
    }

    QLength distanceToPoint(QLength x, QLength y) {}

    QAngle angleToPoint(QLength x, QLength y) {}

    std::tuple<QLength, QAngle> distanceAndAngleToPoint(QLength x, QLength y) {
        return std::tuple<QLength, QAngle>(distanceToPoint(x, y), angleToPoint(x, y));
    }

    void run(void* p) {}
}