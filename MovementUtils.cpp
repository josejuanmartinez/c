//
// Created by jjmca on 15/04/2022.
//

#include <vector>
#include "MovementUtils.h"
#include "MathUtils.h"
#include <climits>
#include <iostream>

using std::cout; using std::cin;
using std::endl; using std::string;
using std::vector; using std::pair;
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
                               const std::vector<int>& Map,
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
                              const std::vector<int>& Map,
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
                           const std::vector<int>& Map,
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
                             const std::vector<int>& Map,
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
                             const std::vector<int>& Map,
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
/*
int MovementUtils::CanGoDownLeft(const std::pair<int,int>& Position,
                             const std::vector<int>& Map,
                             const std::pair<int, int>& MapDimensions) {
    //std::pair<int,int> node = Position;
    //node.second--;
    int newPosX = Position.first - 1;
    int newPosY = Position.second - 1;
    if (CanMoveTo({newPosX, newPosY}, Map, MapDimensions)) {
        return MathUtils::Transpose({newPosX, newPosY}, MapDimensions);
    } else {
        return -1;
    }
}

int MovementUtils::CanGoDownRight(const std::pair<int,int>& Position,
                                 const std::vector<int>& Map,
                                 const std::pair<int, int>& MapDimensions) {
    //std::pair<int,int> node = Position;
    //node.second--;
    int newPosX = Position.first + 1;
    int newPosY = Position.second - 1;
    if (CanMoveTo({newPosX, newPosY}, Map, MapDimensions)) {
        return MathUtils::Transpose({newPosX, newPosY}, MapDimensions);
    } else {
        return -1;
    }
}

int MovementUtils::CanGoUpLeft(const std::pair<int,int>& Position,
                                  const std::vector<int>& Map,
                                  const std::pair<int, int>& MapDimensions) {
    //std::pair<int,int> node = Position;
    //node.second--;
    int newPosX = Position.first - 1;
    int newPosY = Position.second + 1;
    if (CanMoveTo({newPosX, newPosY}, Map, MapDimensions)) {
        return MathUtils::Transpose({newPosX, newPosY}, MapDimensions);
    } else {
        return -1;
    }
}

int MovementUtils::CanGoUpRight(const std::pair<int,int>& Position,
                               const std::vector<int>& Map,
                               const std::pair<int, int>& MapDimensions) {
    //std::pair<int,int> node = Position;
    //node.second--;
    int newPosX = Position.first + 1;
    int newPosY = Position.second + 1;
    if (CanMoveTo({newPosX, newPosY}, Map, MapDimensions)) {
        return MathUtils::Transpose({newPosX, newPosY}, MapDimensions);
    } else {
        return -1;
    }
}*/

/**
 *
 * @param node A Current node (cell)
 * @param Map  The map with obstacles
 * @param MapDimensions The w,h dimensions
 * @return A vector of positions
 */
std::vector<int> MovementUtils::GetNeighbours(const std::pair<int,int>& Position, const std::vector<int>& Map,
                                              const std::pair<int, int>& MapDimensions) {

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
* Auxiliar heuristic to check if exploring a node is a good idea depending on the surroundings
* @param node A Current node (cell)
* @param Map  The map with obstacles
* @param MapDimensions The w,h dimensions
* @return A vector of positions
*/
/*
int MovementUtils::GetObstacles(const std::pair<int,int>& Current, const std::vector<int>& Map,
                                              const std::pair<int, int>& MapDimensions) {

    int res = 0;
    int resDown = MovementUtils::CanGoDown(Current, Map, MapDimensions);
    int resLeft = MovementUtils::CanGoLeft(Current, Map, MapDimensions);
    int resUp = MovementUtils::CanGoUp(Current, Map, MapDimensions);
    int resRight = MovementUtils::CanGoRight(Current, Map, MapDimensions);
    int resDownLeft = MovementUtils::CanGoDownLeft(Current, Map, MapDimensions);
    int resDownRight = MovementUtils::CanGoDownRight(Current, Map, MapDimensions);
    int resUpLeft = MovementUtils::CanGoUpLeft(Current, Map, MapDimensions);
    int resUpRight = MovementUtils::CanGoUpRight(Current, Map, MapDimensions);
    if (resDown == -1)
        res++;
    if (resUp == -1)
        res++;
    if (resLeft == -1)
        res++;
    if (resRight == -1)
        res++;
    if (resDownLeft == -1)
        res++;
    if (resDownRight == -1)
        res++;
    if (resUpLeft == -1)
        res++;
    if (resUpRight == -1)
        res++;
    return res;
}
*/
/*
int MovementUtils::GetScore(const std::pair<int,int>& Start, const std::pair<int,int>& Target, const std::pair<int,int>& Current, const std::pair<int, int>& MapDimensions, const std::vector<int> &Map) {
    //int distance_to_target = MathUtils::ManhattanDistance(Current, Target);    // the lesser the better!
    //int distance_to_start = -1 * MathUtils::ManhattanDistance(Current, Start); // the bigger the better!
    //int penalty = MovementUtils::GetObstacles(Current, Map, MapDimensions);

    //int all = distance_to_start + distance_to_target + penalty;
    //int all = distance_to_start + distance_to_target;
    /*std::cout << "-- " << Current.first << "," << Current.second << "\n";
    std::cout << "--- Distance to target: " << distance_to_target << "\n";
    std::cout << "--- Distance to start: " << distance_to_start << "\n";
    std::cout << "--- Penalty: " << penalty << "\n";
    std::cout << "---- All: " << all << "\n";*/
/*
    return MathUtils::ManhattanDistance(Current, Target) - MathUtils::ManhattanDistance(Current, Target);
}*/

/*
 * In Djikstra, we select next node to visit per the cost of visiting it. Since we costs are equal,
 * we are going to select depending on the distance to the end, PRESUPPOSING we have no obstacles (we may be wrong,
 * but this is a greedy way to try to improve on the best cases)
 */
int MovementUtils::GetClosestCandidate(const std::vector<std::pair<int, int>>& toVisit, const std::pair<int, int>& MapDimensions) {
    int best_distance = INT_MAX;
    int min_node;

    for(int i=0;i<toVisit.size();i++) {
        if (toVisit[i].second < best_distance) {
            min_node = i;
            best_distance = toVisit[i].second;
        }
    }

    //std::cout << "--The closest candidate is " << MathUtils::Untranspose(toVisit[min_node].first, MapDimensions).first << "," << MathUtils::Untranspose(toVisit[min_node].first, MapDimensions).second << " !!!!!!!!\n";
    return min_node;
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