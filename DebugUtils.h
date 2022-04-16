//
// Created by jjmca on 15/04/2022.
//

#ifndef PATHFINDER_DEBUGUTILS_H
#define PATHFINDER_DEBUGUTILS_H

#include <vector>

class DebugUtils {
    public:
        static void PrintPosition(const std::pair<int,int>&, const std::string&, const int&);
        static void PrintDistance(const int&, const int&, const int&);
        static void PrintDistances(const std::vector<int>&, const std::pair<int, int>&);
        static void PrintClosest(const std::vector<int>&, const std::pair<int, int>&);
        static void PrintPositionSlim(const std::pair<int, int>&);
};


#endif //PATHFINDER_DEBUGUTILS_H
