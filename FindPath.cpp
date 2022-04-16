#include <vector>
#include "MathUtils.h"
#include "MovementUtils.h"
#include <algorithm>
#include "DebugUtils.h"
#include "FindPath.h"

bool FindPath::ShortestPath(std::pair<int, int> Start,
              std::pair<int, int> Target,
              const std::vector<bool>& Map,
              std::pair<int, int> MapDimensions,
              std::vector<int>& OutPath) {

    // EDGE CASES:
    // ==========
    // If Start = Target, then a path exists (with length ).
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

    // I work with ints
    int iStart = MathUtils::Transpose(Start, MapDimensions);
    int iTarget = MathUtils::Transpose(Target, MapDimensions);

    // NON-EDGE CASES:
    // ==========

    // Initialization of distances and closest-node matrix
    std::vector<int> distances (MapDimensions.first * MapDimensions.second, -1);
    std::vector<int> closest (MapDimensions.first * MapDimensions.second, -1);
    distances[iStart] = 0;

    // Initialization of queues and closest-node matrix
    // toVisit is a queue, I only need to add and remove, not search or insert/delete in the middle
    std::vector<int> toVisit;
    // visited: I need to check if a node is already visited, so I transverse all the array, It can not be a queue
    std::vector<int> visited;

    // START
    // First, we push the beginning to 'toVisit'
    toVisit.push_back(MathUtils::Transpose(Start, MapDimensions));

    while(!toVisit.empty()) {
        // I take one available node, remove it from toVisit and add it to visited
        int popped = toVisit.back();
        toVisit.pop_back();
        visited.push_back(popped);
        //DebugUtils::PrintPosition(popped, "Exploring", 1, MapDimensions);

        // I retrieve  the accumulated (shorted) cost to reach the popped node
        int popped_distance = distances[popped];

        // I get its neighbours
        std::vector<int> neighbors = MovementUtils::GetNeighbours(popped, Map, MapDimensions);

        // I check the distances from the node to the neighbours
        for(int neighbor: neighbors) {
            //DebugUtils::PrintPosition(neighbor, "Neighbour", 2, MapDimensions);
            // I get the new distance
            int new_distance = popped_distance + 1;
            //std::cout << "--New distance: " << new_distance << "\n";
            int neighbor_distance = distances[neighbor];
            // If the distance is smaller than other ways or it's first time, I update it as the shortest path and update the closest node
            if (new_distance < neighbor_distance || neighbor_distance == -1) {
                //int transposedNeighbour = MathUtils::Transpose(neighbor, MapDimensions);
                distances[neighbor] = new_distance;
                closest[neighbor] = popped;
                //std::cout << "--- Shorter path: "  << new_distance << " vs. "<< neighbor_distance << "\n";

                // I need to revisit my neighbor
                toVisit.push_back(neighbor);
            }
            /*else {
                 std::cout << "--- Non-sorther path: "  << new_distance << " vs. "<< neighbor_distance << "\n";
            }*/

        }
    }
    //DebugUtils::PrintDistancesAndClosest(distances, closest, MapDimensions);

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
