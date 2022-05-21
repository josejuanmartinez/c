#include <vector>
#include "MathUtils.h"
#include "MovementUtils.h"
#include <algorithm>
#include "DebugUtils.h"
#include "FindPath.h"

bool FindPath::ShortestPath(std::pair<int, int> Start,
                            std::pair<int, int> Target,
                            const std::vector<int>& Map,
                            std::pair<int, int> MapDimensions,
                            std::vector<int>& OutPath) {

    // EDGE CASES:
    // ==========
    // If Start = Target, then a path exists (with length 0).
    if(Start == Target) {
        return true;
    }
    // Start is impassable
    if(Map[MathUtils::Transpose(Start, MapDimensions)] == 0) {
        return false;
    }
    // Start out of the map
    if(MovementUtils::IsOutsideMap(Start, MapDimensions)) {
        return false;
    }
    // Target is impassable
    if(Map[MathUtils::Transpose(Target, MapDimensions)] == 0) {
        return false;
    }
    // Target outside the map
    if(MovementUtils::IsOutsideMap(Start, MapDimensions)) {
        return false;
    }

    // Transpose a 2D cell into its 1D representation in a vector
    int iStart = MathUtils::Transpose(Start, MapDimensions);
    int iTarget = MathUtils::Transpose(Target, MapDimensions);

    // NON-EDGE CASES:
    // ==========

    // I set a max_distance to prevent the algorithm going fart
    int MAX_DISTANCE = MathUtils::ManhattanDistance(Start, Target) * 750;

    // Initialization of distances and closest-node matrix
    std::vector<int> distances (MapDimensions.first * MapDimensions.second, -1);
    std::vector<int> closest (MapDimensions.first * MapDimensions.second, -1);
    distances[iStart] = 0;

    // Initialization of queues and closest-node matrix
    // toVisit is a queue, I only need to add and remove, not search or insert/delete in the middle
    std::vector<std::pair<int, int>> toVisit;
    // visited: I need to check if a node is already visited, so I transverse all the array, It can not be a queue
    std::vector<int> visited;

    // START
    // First, we push the beginning to 'toVisit'
    int popped = iStart;

    // I store {node, score}
    //toVisit.emplace_back(popped, 0);

    //GREEDY APPROACH: I TRY TO FIND IT ALL STRAIGHT IN X AND THEN IN Y
    bool bRight = Start.first < Target.first;
    int iX = Start.first;
    int greedy_distance = distances[iStart];
    for(; iX<Target.first;) {

        std::pair<int,int> tr_neighbor = {iX+1, Start.second};
        if (!MovementUtils::CanMoveTo(tr_neighbor, Map, MapDimensions)) {
            break;
        }

        int neighbor = MathUtils::Transpose(tr_neighbor, MapDimensions);
        distances[neighbor] = ++greedy_distance;
        closest[neighbor] = popped;
        //toVisit.emplace_back(neighbor, MathUtils::ManhattanDistance(tr_neighbor, Target) - MathUtils::ManhattanDistance(tr_neighbor, Target));
        if (bRight)
            iX++;
        else
            iX--;
        popped = neighbor;
        bRight = iX < Target.first;
    }
    bool bUp = Start.second < Target.second;
    int iY = Start.second;
    for(; iY<Target.second;) {
        std::pair<int,int> tr_neighbor = {iX, iY+1};
        if (!MovementUtils::CanMoveTo(tr_neighbor, Map, MapDimensions)) {
            break;
        }
        int neighbor = MathUtils::Transpose(tr_neighbor, MapDimensions);
        distances[neighbor] = ++greedy_distance;
        closest[neighbor] = popped;
        //toVisit.emplace_back(neighbor, MathUtils::ManhattanDistance(tr_neighbor, Target) - MathUtils::ManhattanDistance(tr_neighbor, Target));
        if (bUp)
            iY++;
        else
            iY--;
        popped = neighbor;
        bUp = iY< Target.second;
    }

    if(iX == Target.first && iY == Target.second) {
        return FindPath::RecreatePath(iStart, iTarget, closest, OutPath);
    }
    else
    {
        //popped = iStart;
        toVisit.emplace_back(iStart, 0);
        fill(distances.begin(), distances.end(), -1);
        fill(closest.begin(), closest.end(), -1);
    }

    while(!toVisit.empty()) {
        // I take one available node, remove it from toVisit and add it to visited
        int popped_pos = MovementUtils::GetClosestCandidate(toVisit, MapDimensions);
        popped = toVisit[popped_pos].first; // {node}
        std::pair<int,int> utr_popped = MathUtils::Untranspose(popped, MapDimensions);
        toVisit.erase(toVisit.begin() + popped_pos);
        visited.push_back(popped);
        //DebugUtils::PrintPosition(popped, "Exploring", 1, MapDimensions);

        // I retrieve  the accumulated (shorted) cost to reach the popped node
        int popped_distance = distances[popped];
        // I calculate the distance to the neighbours from the popped node
        int new_distance = popped_distance + 1;

        if (new_distance >= MAX_DISTANCE) {
            continue;
        }

        // I get its neighbours
        std::vector<int> neighbors = MovementUtils::GetNeighbours(utr_popped, Map, MapDimensions);

        // I check the distances from the node to the neighbours
        for(int neighbor: neighbors) {
            std::pair<int,int> tr_neighbor = MathUtils::Untranspose(neighbor, MapDimensions);
            //DebugUtils::PrintPosition(neighbor, "Neighbour", 2, MapDimensions);
            //std::cout << "--New distance: " << new_distance << "\n";
            int neighbor_distance = distances[neighbor];

            // When I add it back to the queue for revision?
            // If unvisited node
            // If I'm better "closest node" than my neighbor's selected closest. This happens if:
            // - 1) It decreases the distance to my neighbor
            // - 2) AND I was not already the closest

            // Manhattan is the closest distance it may be (straight line). If it's bigger than a found path, desist
            int manhattan = MathUtils::ManhattanDistance(tr_neighbor, Target);
            if (distances[iTarget] != -1 && (popped_distance + manhattan + 1) >= distances[iTarget]) {
                //std::cout << "Skipping visiting neighbors of " << utr_popped.first << "," << utr_popped.second << " because it's distance is " << popped_distance << " and the distance to the target is " << distances[iTarget] << " and Manhattan distance is " << manhattan << "\n";
                continue;
            }

            if ( new_distance < neighbor_distance || neighbor_distance == -1 ) {
                distances[neighbor] = new_distance;
                //if (neighbor == iTarget) {
                //std::cout << "Updating best path distance to target. Distance: " << new_distance << ". From: " << popped << "\n";
                //}
                closest[neighbor] = popped;
                //std::cout << "--- Shorter path: "  << new_distance << " vs. "<< neighbor_distance << "\n";

                // If this path is less costly than any previously found path to Target, I add the node

                // Was it already planned to visit this node? If so, don't check it again
                bool bFound = false;
                for(auto & i : toVisit) {
                    if (i.first == neighbor) {
                        bFound = true;
                        break;
                    }
                }

                if(!bFound) {
                    // I will reduce score to those nodes already visited, but never removed because a cell can be part of many paths
                    //if(find(visited.begin(), visited.end(), neighbor) != visited.end()) {
                    //       distance *= 2;
                    //}

                    toVisit.emplace_back(neighbor, MathUtils::ManhattanDistance(tr_neighbor, Target) - MathUtils::ManhattanDistance(tr_neighbor, Target));
                    //DebugUtils::PrintPosition(neighbor, "Adding Neighbour to list", 2, MapDimensions);
                }
                //else {
                //    std::cout << "Skipping visiting node " << neighbor << " because it's distance is " << distances[neighbor] << " and the distance to the target is " << distances[iTarget] << "\n";
                //}
            }
            /*else {
                 std::cout << "--- Non-sorther path: "  << new_distance << " vs. "<< neighbor_distance << "\n";
            }*/

        }
    }
    //DebugUtils::PrintDistancesAndClosest(distances, closest, MapDimensions);
    return FindPath::RecreatePath(iStart, iTarget, closest, OutPath);
}

bool FindPath::RecreatePath(const int& iStart, const int &iTarget, const std::vector<int>& closest, std::vector<int>& OutPath) {
    // I reconstruct the path from the Target to the Source using the closest nodes
    int next = iTarget;
    while(next != iStart) {
        if (next == -1) {
        OutPath = std::vector<int>();
        return false;
    }
    //DebugUtils::PrintPosition(MathUtils::Untranspose(next, MapDimensions), "Closest", 1);
    OutPath.push_back(next);
    next = closest[next];
    }
    std::reverse(OutPath.begin(), OutPath.end());
    return true;
}