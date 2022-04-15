//
// Created by jjmca on 15/04/2022.
//

#include <iostream>
#include "DebugUtils.h"
#include "MathUtils.h"

/**
 * Prints a sentence with the cell/position
 * @param Position
 * @param name
 * @param indent
 */
void DebugUtils::PrintPosition(std::pair<int, int> Position, const std::string& name, int indent) {
    std::cout << std::string(indent, '-') << name << ": (" << Position.first << "," << Position.second << ")" << "\n";
}

/**
 * Prints just the position
 * @param Position
 */
void DebugUtils::PrintPositionSlim(std::pair<int, int> Position) {
    std::cout << "(" << Position.first << "," << Position.second << ")";
}

/**
 * Prints a distance from coordinates
 * @param i
 * @param j
 * @param distance
 */
void DebugUtils::PrintDistance(int i, int j, int distance) {
    std::cout << "(" << i << "," << j << ")=" << distance <<" ";
}

/**
 * Prints the distance matrix
 * @param distances
 * @param MapDimensions
 */
void DebugUtils::PrintDistances(std::vector<int> distances, std::pair<int, int> MapDimensions) {
    for (int j=MapDimensions.second-1;j>=0;j--) {
        for (int i=0;i<MapDimensions.first;i++) {
            int distance = distances[MathUtils::Transpose({i, j}, MapDimensions)];
            DebugUtils::PrintDistance(i, j , distance);
        }
        std::cout << "\n";
    }
}

/**
 * Prints the closest-nodes matrix
 * @param closests
 * @param MapDimensions
 */
void DebugUtils::PrintClosest(std::vector<std::pair<int, int>> closests, std::pair<int, int> MapDimensions) {
    for (int j=MapDimensions.second-1;j>=0;j--) {
        for (int i=0;i<MapDimensions.first;i++) {
            std::pair<int, int> closest = closests[MathUtils::Transpose({i, j}, MapDimensions)];
            DebugUtils::PrintPositionSlim({i,j});
            std::cout << "=";
            DebugUtils::PrintPositionSlim(closest);
            std::cout << " ";
        }
        std::cout << "\n";
    }
}
