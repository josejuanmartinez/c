//
// Created by jjmca on 15/04/2022.
//

#include <vector>
#include "MovementUtils.h"
#include "MathUtils.h"

/**
 * Is Target Position inside the map?
 * @param Position Target Position
 * @param MapDimensions  Max width and height of the map
 * @return bool
 */
bool MovementUtils::IsOutsideMap(const std::pair<int,int>& Position,
                                 const std::pair<int, int>& MapDimensions) {
    bool res = (Position.first >= MapDimensions.first || Position.second >= MapDimensions.second || Position.first <0 || Position.second < 0);
    //DebugUtils::PrintPosition(Position, res ? "True" : "False", 0);
    return res;
}

/**
 * Is Target position inside the boundaries and passable?
 * @param Position Target Position
 * @param Map Cells with bools (true=passable, false=impassable)
 * @param MapDimensions  Max width and height of the map
 * @return bool
 */
bool MovementUtils::CanMoveTo (const std::pair<int,int>& Position,
                               const std::vector<bool>& Map,
                               const std::pair<int, int>& MapDimensions) {
    return (!IsOutsideMap(Position, MapDimensions) && Map[MathUtils::Transpose(Position, MapDimensions)]);
}

/**
 * Can I move right?
 * @param Position Target Position
 * @param Map Cells with bools (true=passable, false=impassable)
 * @param MapDimensions  Max width and height of the map
 * @return int
 */
int MovementUtils::CanGoRight(const std::pair<int,int>& Position,
                               const std::vector<bool>& Map,
                               const std::pair<int, int>& MapDimensions) {
    //std::pair<int,int> node = Position;
    int newPos = Position.first + 1;
    if (CanMoveTo({newPos, Position.second}, Map, MapDimensions)) {
        return MathUtils::Transpose({newPos, Position.second}, MapDimensions);
    } else {
        return -1;
    }
}

/**
 * Can I move up?
 * @param Position Target Position
 * @param Map Cells with bools (true=passable, false=impassable)
 * @param MapDimensions  Max width and height of the map
 * @return int
 */
int MovementUtils::CanGoUp(const std::pair<int,int>& Position,
                           const std::vector<bool>& Map,
                           const std::pair<int, int>& MapDimensions) {
    //std::pair<int,int> node = Position;
    //node.second++;
    int newPos = Position.second + 1;
    if (CanMoveTo({Position.first, newPos}, Map, MapDimensions)) {
        return MathUtils::Transpose({Position.first, newPos}, MapDimensions);
    } else {
        return -1;
    }
}

/**
 * Can I move left?
 * @param Position Target Position
 * @param Map Cells with bools (true=passable, false=impassable)
 * @param MapDimensions  Max width and height of the map
 * @return int
 */
int MovementUtils::CanGoLeft(const std::pair<int,int>& Position,
                             const std::vector<bool>& Map,
                             const std::pair<int, int>& MapDimensions) {
    //std::pair<int,int> node = Position;
    //node.first--;
    int newPos = Position.first - 1;
    if (CanMoveTo({newPos, Position.second}, Map, MapDimensions)) {
        return MathUtils::Transpose({newPos, Position.second}, MapDimensions);
    } else {
        return -1;
    }
}

/**
 * Can I move down?
 * @param Position Target Position
 * @param Map Cells with bools (true=passable, false=impassable)
 * @param MapDimensions  Max width and height of the map
 * @return int
 */
int MovementUtils::CanGoDown(const std::pair<int,int>& Position,
                             const std::vector<bool>& Map,
                             const std::pair<int, int>& MapDimensions) {
    //std::pair<int,int> node = Position;
    //node.second--;
    int newPos = Position.second - 1;
    if (CanMoveTo({Position.first, newPos}, Map, MapDimensions)) {
        return MathUtils::Transpose({Position.first, newPos}, MapDimensions);
    } else {
        return -1;
    }
}

/**
 *
 * @param node A Current node (cell)
 * @param Map  The map with obstacles
 * @param MapDimensions The w,h dimensions
 * @return A vector of positions
 */
std::vector<int> MovementUtils::GetNeighbours(const int& node, const std::vector<bool>& Map,
                                              const std::pair<int, int>& MapDimensions) {

    std::pair<int, int> Position = MathUtils::Untranspose(node, MapDimensions);
    std::vector<int> res;
    int resDown = MovementUtils::CanGoDown(Position, Map, MapDimensions);
    int resLeft = MovementUtils::CanGoLeft(Position, Map, MapDimensions);
    int resUp = MovementUtils::CanGoUp(Position, Map, MapDimensions);
    int resRight = MovementUtils::CanGoRight(Position, Map, MapDimensions);
    if (resDown != -1)
        res.push_back(resDown);
    if (resUp != -1)
        res.push_back(resUp);
    if (resLeft != -1)
        res.push_back(resLeft);
    if (resRight != -1)
        res.push_back(resRight);
    return res;
}

/**
 * Some unit tests...
 */
/*void MovementUtils::Test() {
    assert(MovementUtils::IsOutsideMap(std::pair(9,9),std::pair(10,10)) == false);
    assert(MovementUtils::IsOutsideMap(std::pair(0,0),std::pair(10,10)) == false);
    assert(MovementUtils::IsOutsideMap(std::pair(10,0),std::pair(10,10)) == true);
    assert(MovementUtils::IsOutsideMap(std::pair(0,10),std::pair(10,10)) == true);
    assert(MovementUtils::IsOutsideMap(std::pair(10,10),std::pair(10,10)) == true);
}
*/