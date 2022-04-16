//
// Created by jjmca on 16/04/2022.
//

#ifndef PATHFINDER_FINDPATH_H
#define PATHFINDER_FINDPATH_H

#include <vector>

class FindPath {
    public:
        static bool ShortestPath(std::pair<int, int> Start,
                             std::pair<int, int> Target,
                             const std::vector<bool>& Map,
                             std::pair<int, int> MapDimensions,
                             std::vector<int>& OutPath);
};


#endif //PATHFINDER_FINDPATH_H