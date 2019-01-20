#pragma once

#include "path.hpp"

namespace path {
    class Line : public Path {
        private:
        Point start;
        Point end;
        
        public:
        Line(Point start, Point end, int resolution);
        Point pointAt(int t);
    };
}