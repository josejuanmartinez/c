//
// Created by jjmca on 15/04/2022.
//

#include "MathUtils.h"
#include <vector>


/*
 * (0,h-1) ...   ...  ... (w-1, h-1)
 * ...                       ...
 * ...                       ...
 * ...                       ...
 * ...                       ...
 * ...                       ...
 * (0,0)   (1,0) (2,0) ... (w-1, 0)
 */


/*
 * Transpose: max_w * h + w
 * Example: (3,5) means row=3 col=5, what means 5(h) times full width and 3(w) positions
 */

/**
 * Transforms 2D into 1D position
 * @param Position Current position in map
 * @param MapDimensions Max width and height
 * @return int
 */
int MathUtils::Transpose(std::pair<int,int> Position, std::pair<int, int> MapDimensions) {
        int res = MapDimensions.first * Position.second + Position.first;
        // std::cerr << "(" << Position.first << "," << Position.second << ")=" << res << "\n";
        return res;
}

/***
 * Returns a vector to reach Target from Source
 * @param Source Where am I?
 * @param Target Where do I need to go?
 * @return Vector pointing from source to target
 */
std::pair<int,int> MathUtils::LookTo(std::pair<int,int> Source, std::pair<int,int> Target) {
    return {Target.first - Source.first, Target.second - Target.first};
}

/**
 * Some unit tests...
 */
void MathUtils::Test() {
        assert(MathUtils::Transpose(std::pair(1,2),std::pair(10,10)) == 21);
        assert(MathUtils::Transpose(std::pair(3,5),std::pair(10,10)) == 53);
        assert(MathUtils::Transpose(std::pair(0,0),std::pair(10,10)) == 0);
        assert(MathUtils::Transpose(std::pair(9,9),std::pair(10,10)) == 99);
}