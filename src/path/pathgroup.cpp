#include "pathgroup.hpp"

namespace path {
    PathGroup::PathGroup(std::initializer_list<Path> list, int resolution, int lookahead) : 
    Path::Path(resolution, lookahead),
    paths(list) {}
    
    Point PathGroup::pointAt(int t) {
        int runningSum = 0;
        for (Path path : paths) {
            int lastRunningSum = runningSum;
            runningSum += path.getResolution();
            if (t <= runningSum) {
                return path.pointAt(t - lastRunningSum);
            }
        }
    }
}