#include <vector>
#include "MathUtils.h"
#include "MovementUtils.h"
#include <algorithm>
#include "DebugUtils.h"

bool FindPath(std::pair<int, int> Start,
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
    distances[0] = 0;

    // Initialization of queues and closest-node matrix
    // toVisit is a queue, I only need to add and remove, not search or insert/delete in the middle
    std::vector<int> toVisit;
    // visited: I need to check if a node is already visited, so I transverse all the array, It can not be a queue
    std::vector<int> visited;

    // This is an optimization: If I see I'm going further than an already found path, I will skip
    int foundDistance = INT16_MAX;

    // START
    // First, we push the beginning to 'toVisit'
    toVisit.push_back(MathUtils::Transpose(Start, MapDimensions));

    while(!toVisit.empty()) {
        // I take one available node, remove it from toVisit and add it to visited
        int popped = toVisit.back();
        toVisit.pop_back();
        visited.push_back(popped);
        // DebugUtils::PrintPosition(popped, "Exploring", 1);

        // I retrieve  the accumulated (shorted) cost to reach the popped node
        int popped_distance = distances[popped];

        // Optimization: If this is taking longer than other finished paths, I skip it
        if (popped_distance >= foundDistance) {
            continue;
        }

        // I get its neighbours
        std::vector<int> neighbors = MovementUtils::GetNeighbours(popped, Map, MapDimensions);

        // I check the distances from the node to the neighbours
        for(int neighbor: neighbors) {
            // DebugUtils::PrintPosition(neighbor, "Neighbour", 2);
            // I get the new distance
            int new_distance = popped_distance + 1;
            // std::cout << "--New distance: " << new_distance << "\n";
            int neighbor_distance = distances[neighbor];
            // If the distance is smaller than other ways or it's first time, I update it as the shortest path and update the closest node
            if (new_distance < neighbor_distance || neighbor_distance == -1) {
                //int transposedNeighbour = MathUtils::Transpose(neighbor, MapDimensions);
                distances[neighbor] = new_distance;
                closest[neighbor] = popped;
                // std::cout << "--- Shorter path: "  << new_distance << " vs. "<< neighbor_distance << "\n";
            }
            // else {
            //     std::cout << "--- Non-sorther path: "  << new_distance << " vs. "<< neighbor_distance << "\n";
            // }
            // If I found the Target, I check if this distance is shorter to ignore other future longer paths
            if (neighbor == iTarget && foundDistance > new_distance) {
                foundDistance = distances[neighbor];
            }
            // I add the node to be visited if it was not visited already
            // I CAN VISIT NODES SEVERAL TIMES!!!
            if (std::find(visited.begin(), visited.end(), neighbor) == visited.end()) {
                // Not found, we add it
                toVisit.push_back(neighbor);
                // DebugUtils::PrintPosition(neighbor, "Unvisited and added to the queue", 3);
            }
        }
    }
    //DebugUtils::PrintDistances(distances, MapDimensions);
    //std::cout << "\n";
    //DebugUtils::PrintClosest(closest, MapDimensions);
    //std::cout << "\n";

    // I reconstruct the path from the Target to the Source using the closest nodes
    int next = iTarget;
    while(next != iStart) {
        if (next == -1) {
            OutPath = std::vector<int>();
            return false;
        }
        //DebugUtils::PrintPosition(next, "Closest", 1);
        OutPath.push_back(next);
        next = closest[next];
    }
    std::reverse(OutPath.begin(), OutPath.end());

    return true;
}

/** TESTING SCENARIOS **/

void test_path_1() {
    std::vector<bool> Map = {1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1};
    std::vector<int> OutPath;
    assert(FindPath({0, 0}, {1, 2}, Map, {4, 3}, OutPath));
    std::vector<int> Expected = {1, 5, 9};
    for(int i=0;i<OutPath.size();i++) {
        //std::cout << OutPath[i] << " " << Expected[i] << "\n";
        assert(OutPath[i] == Expected[i]);
    }
}

void test_path_2() {
    std::vector<bool> Map = {0, 0, 1, 0, 1, 1, 1, 0, 1};
    std::vector<int> OutPath;
    assert(!FindPath({2, 0}, {0, 2}, Map, {3, 3}, OutPath));
    assert(OutPath.empty());
}


void test_path_3() {
    std::vector<bool> Map = {1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1 ,1 ,1};
    std::vector<int> OutPath;
    assert(FindPath({0, 0}, {3, 3}, Map, {4, 4}, OutPath));
    std::vector<int> Expected = {4, 8, 12, 13, 14, 15};
    for(int i=0;i<OutPath.size();i++) {
        //std::cout << OutPath[i] << " " << Expected[i] << "\n";
        assert(OutPath[i] == Expected[i]);
    }
}

void test_path_4() {
    std::vector<bool> Map = {1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0 ,1 ,1};
    std::vector<int> OutPath;
    assert(!FindPath({0, 0}, {3, 3}, Map, {4, 4}, OutPath));
    assert(OutPath.empty());
}

int main() {
    //MathUtils::Test();
    //MovementUtils::Test();
    //test_path_1();
    //test_path_2();
    //test_path_3();
    //test_path_4();
}
