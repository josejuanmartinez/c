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
        static std::vector<std::pair<int, int>> GetNeighbours(std::pair<int, int> node, const std::vector<bool> &Map, std::pair<int, int> MapDimensions);
        static bool IsOutsideMap(std::pair<int,int>, std::pair<int, int>);
        static bool CanMoveTo (std::pair<int,int>, const std::vector<bool>& Map, std::pair<int, int>);
        static std::pair<int,int> CanGoRight(std::pair<int,int>, const std::vector<bool>& Map, std::pair<int, int>);
        static std::pair<int,int> CanGoUp(std::pair<int,int>, const std::vector<bool>& Map, std::pair<int, int>);
        static std::pair<int,int> CanGoLeft(std::pair<int,int>, const std::vector<bool>& Map, std::pair<int, int>);
        static std::pair<int,int> CanGoDown(std::pair<int,int>, const std::vector<bool>& Map, std::pair<int, int>);
        static void Test();
};


#endif //PATHFINDER_MOVEMENTUTILS_H
