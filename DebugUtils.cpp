//
// Created by jjmca on 15/04/2022.
//

#include <iostream>
#include "DebugUtils.h"
#include "MathUtils.h"

void DebugUtils::PrintPosition(std::pair<int, int> Position, const std::string& name, int indent) {
    std::cout << std::string(indent, '-') << name << ": (" << Position.first << "," << Position.second << ")" << "\n";
}

void DebugUtils::PrintPositionSlim(std::pair<int, int> Position) {
    std::cout << "(" << Position.first << "," << Position.second << ")";
}

void DebugUtils::PrintDistance(int i, int j, int distance) {
    std::cout << "(" << i << "," << j << ")=" << distance <<" ";
}

void DebugUtils::PrintDistances(std::vector<int> distances, std::pair<int, int> MapDimensions) {
    for (int j=MapDimensions.second-1;j>=0;j--) {
        for (int i=0;i<MapDimensions.first;i++) {
            int distance = distances[MathUtils::Transpose({i, j}, MapDimensions)];
            DebugUtils::PrintDistance(i, j , distance);
        }
        std::cout << "\n";
    }
}

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
