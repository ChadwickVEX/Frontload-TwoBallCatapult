#pragma once

#include "okapi/api/units/QLength.hpp"

namespace path {  
 
    struct Point {
        okapi::QLength x;
        okapi::QLength y;
    };

    class Path {
        private:
        int currT;

        protected:
        int resolution;

        public:
        Path(int resolution);
        
        /**
         * Get next point on path
         */
        Point nextPoint();

        /**
         * Get Point at parametric T
         */
        virtual Point pointAt(int T);
        
        /**
         * Get the nearest point to input on the path via seraching them all
         */
        double computeSmallestDistance(double x, double y);

        int getResolution();
    };
}