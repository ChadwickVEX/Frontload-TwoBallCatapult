#include "main.h"

namespace drive {
    /**
     * [-1.0, 1.0]
     */
    void moveVoltage(double left, double right) {
        if (left == 0) {
            mtrLB.moveVelocity(0);
            mtrLF.moveVelocity(0);
        } else {
            mtrLF.moveVoltage(left * 12000);
            mtrLB.moveVoltage(left * 12000);
        }

        if (right == 0) {
            mtrRB.moveVelocity(0);
            mtrRF.moveVelocity(0);
        } else {
            mtrRB.moveVoltage(right * 12000);
            mtrRF.moveVoltage(right * 12000);
        }

    }
}