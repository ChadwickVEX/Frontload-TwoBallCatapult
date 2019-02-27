#include "path.hpp"
#include <vector>
#include <functional>

namespace path {
    class Bezier : public Path {
        private:
        std::vector<Point> points;

        int factorial(int n);
        double combination(int n, int r);

        public:
        Bezier(std::initializer_list<Point> points, int resolution, int lookahead = -1);

        Point pointAt(int T);
    };
}