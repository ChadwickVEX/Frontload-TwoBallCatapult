#include "bezier.hpp"

namespace path {
    Bezier::Bezier(std::initializer_list<std::reference_wrapper<Point>> points, int resolution, int lookahead) : Path::Path(resolution, lookahead),
                                                                                                                points(points) {}
    
    Point Bezier::pointAt(int T) {}
}