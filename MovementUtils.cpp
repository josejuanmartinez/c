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
bool MovementUtils::IsOutsideMap(std::pair<int,int> Position,
                                 std::pair<int, int> MapDimensions) {
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
bool MovementUtils::CanMoveTo (std::pair<int,int> Position,
                               const std::vector<bool>& Map,
                               std::pair<int, int> MapDimensions) {
    return (!IsOutsideMap(Position, MapDimensions) && Map[MathUtils::Transpose(Position, MapDimensions)]);
}

/**
 * Can I move right?
 * @param Position Target Position
 * @param Map Cells with bools (true=passable, false=impassable)
 * @param MapDimensions  Max width and height of the map
 * @return bool
 */
std::pair<int,int> MovementUtils::CanGoRight(std::pair<int,int> Position,
                               const std::vector<bool>& Map,
                               std::pair<int, int> MapDimensions) {
    std::pair<int,int> node = Position;
    node.first++;
    if (CanMoveTo(node, Map, MapDimensions)) {
        return node;
    } else {
        return Position;
    }
}

/**
 * Can I move up?
 * @param Position Target Position
 * @param Map Cells with bools (true=passable, false=impassable)
 * @param MapDimensions  Max width and height of the map
 * @return bool
 */
std::pair<int,int> MovementUtils::CanGoUp(std::pair<int,int> Position,
                                             const std::vector<bool>& Map,
                                             std::pair<int, int> MapDimensions) {
    std::pair<int,int> node = Position;
    node.second++;
    if (CanMoveTo(node, Map, MapDimensions)) {
        return node;
    } else {
        return Position;
    }
}

/**
 * Can I move left?
 * @param Position Target Position
 * @param Map Cells with bools (true=passable, false=impassable)
 * @param MapDimensions  Max width and height of the map
 * @return bool
 */
std::pair<int,int> MovementUtils::CanGoLeft(std::pair<int,int> Position,
                                             const std::vector<bool>& Map,
                                             std::pair<int, int> MapDimensions) {
    std::pair<int,int> node = Position;
    node.first--;
    if (CanMoveTo(node, Map, MapDimensions)) {
        return node;
    } else {
        return Position;
    }
}

/**
 * Can I move down?
 * @param Position Target Position
 * @param Map Cells with bools (true=passable, false=impassable)
 * @param MapDimensions  Max width and height of the map
 * @return bool
 */
std::pair<int,int> MovementUtils::CanGoDown(std::pair<int,int> Position,
                                            const std::vector<bool>& Map,
                                            std::pair<int, int> MapDimensions) {
    std::pair<int,int> node = Position;
    node.second--;
    if (CanMoveTo(node, Map, MapDimensions)) {
        return node;
    } else {
        return Position;
    }
}

/**
 *
 * @param node A Current node (cell)
 * @param Map  The map with obstacles
 * @param MapDimensions The w,h dimensions
 * @return A vector of positions
 */
std::vector<std::pair<int, int>> MovementUtils::GetNeighbours(std::pair<int, int> node, const std::vector<bool>& Map,
                                                             std::pair<int, int> MapDimensions) {
    std::vector<std::pair<int, int>> res;
    std::pair<int, int> resDown = MovementUtils::CanGoDown(node, Map, MapDimensions);
    std::pair<int, int> resLeft = MovementUtils::CanGoLeft(node, Map, MapDimensions);
    std::pair<int, int> resUp = MovementUtils::CanGoUp(node, Map, MapDimensions);
    std::pair<int, int> resRight = MovementUtils::CanGoRight(node, Map, MapDimensions);
    if (resDown != node) {
        res.push_back(resDown);
    }
    if (resUp != node) {
        res.push_back(resUp);
    }
    if (resLeft != node) {
        res.push_back(resLeft);
    }
    if (resRight != node) {
        res.push_back(resRight);
    }
    return res;
}

/**
 * Some unit tests...
 */
void MovementUtils::Test() {
    assert(MovementUtils::IsOutsideMap(std::pair(9,9),std::pair(10,10)) == false);
    assert(MovementUtils::IsOutsideMap(std::pair(0,0),std::pair(10,10)) == false);
    assert(MovementUtils::IsOutsideMap(std::pair(10,0),std::pair(10,10)) == true);
    assert(MovementUtils::IsOutsideMap(std::pair(0,10),std::pair(10,10)) == true);
    assert(MovementUtils::IsOutsideMap(std::pair(10,10),std::pair(10,10)) == true);
}
