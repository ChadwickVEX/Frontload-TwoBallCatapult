#include "line.hpp"
#include "okapi/api/units/QLength.hpp"

namespace path {
    Line::Line(Point start, Point end, int resolution = 100) : Path::Path(resolution), start(start), end(end) {
        // if (resolution <= 0)
        //     throw std::invalid_argument("Adaptive Pure Pursuit Controller resolution cannot be <= 0!");
    }

    Point Line::pointAt(int T) {
        int t = (t > resolution) ? resolution : (t < 0) ? 0 : T;
        double x = (end.x.convert(okapi::inch) * (double) t) / ((double) resolution) + start.x.convert(okapi::inch);
        double y = (end.y.convert(okapi::inch) * (double) t) / ((double) resolution) + start.y.convert(okapi::inch);
        return {x * okapi::inch, y * okapi::inch};
    }
}