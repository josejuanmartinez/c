#include <vector>
#include <algorithm>
#include "FindPath.h"

bool FindPath(std::pair<int, int> Start,
              std::pair<int, int> Target,
              const std::vector<bool>& Map,
              std::pair<int, int> MapDimensions,
              std::vector<int>& OutPath) {

    return FindPath::ShortestPath(Start, Target, Map, MapDimensions, OutPath);
}
