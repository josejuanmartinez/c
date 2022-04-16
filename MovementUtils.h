//
// Created by jjmca on 15/04/2022.
//

#ifndef PATHFINDER_MOVEMENTUTILS_H
#define PATHFINDER_MOVEMENTUTILS_H

#include <iostream>
#include <vector>
#include <cassert>

class MovementUtils {
    public:
        static std::vector<int> GetNeighbours(const int& node, const std::vector<bool> &Map,
                                              const std::pair<int, int>& MapDimensions);
        static bool IsOutsideMap(const std::pair<int,int>&, const std::pair<int, int>&);
        static bool CanMoveTo (const std::pair<int,int>&, const std::vector<bool>& Map, const std::pair<int, int>&);
        static int CanGoRight(const std::pair<int,int>&, const std::vector<bool>& Map, const std::pair<int, int>&);
        static int CanGoUp(const std::pair<int,int>&, const std::vector<bool>& Map, const std::pair<int, int>&);
        static int CanGoLeft(const std::pair<int,int>&, const std::vector<bool>& Map, const std::pair<int, int>&);
        static int CanGoDown(const std::pair<int,int>&, const std::vector<bool>& Map, const std::pair<int, int>&);
        // static void Test();
};


#endif //PATHFINDER_MOVEMENTUTILS_H
