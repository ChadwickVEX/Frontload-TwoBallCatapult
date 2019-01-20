#include "path.hpp"
#include <cmath>

namespace path {
    Path::Path(int resolution) : currT(0), resolution(resolution) {}

    Point Path::nextPoint() {
        return pointAt(++currT);
    }

    double Path::computeSmallestDistance(double x, double y) {
        using namespace okapi;

        Point point = pointAt(0);
        double distanceLeast = sqrt(pow((point.x.convert(meter) - x), 2) + pow((point.y.convert(meter) - y), 2));

        for (int t = 1; t <= resolution; t++) {
            Point tempPoint = pointAt(t);
            double distance = sqrt(pow((tempPoint.x.convert(meter) - x), 2) + pow((tempPoint.y.convert(meter) - y), 2));
            if (distance < distanceLeast) {
                distanceLeast = distance;
            }
        }

        return distanceLeast;
    }
}