#include "path.hpp"
#include <vector>
#include <functional>

namespace path {
    class Bezier : public Path {
        private:
        std::vector<std::reference_wrapper<Point>> points;

        public:
        Bezier(std::initializer_list<std::reference_wrapper<Point>> points, int resolution, int lookahead = -1);

        Point pointAt(int T);
    };
}