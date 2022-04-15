//
// Created by jjmca on 15/04/2022.
//

#ifndef PATHFINDER_DEBUGUTILS_H
#define PATHFINDER_DEBUGUTILS_H

#include <vector>

class DebugUtils {
    public:
        static void PrintPosition(std::pair<int,int>, const std::string&, int);
        static void PrintDistance(int, int, int);
        static void PrintDistances(std::vector<int>, std::pair<int, int>);
        static void PrintClosest(std::vector<std::pair<int, int>>, std::pair<int, int>);
        static void PrintPositionSlim(std::pair<int, int>);
};


#endif //PATHFINDER_DEBUGUTILS_H
