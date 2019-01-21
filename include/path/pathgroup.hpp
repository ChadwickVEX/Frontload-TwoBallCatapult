#pragma once

#include "path.hpp"
#include <vector>

namespace path {
    class PathGroup : public Path {
        private:
        std::vector<Path> paths;
        
        public:
        PathGroup(std::initializer_list<Path> list, int resolution, int lookahead = -1);

        Point pointAt(int t);
    };
}