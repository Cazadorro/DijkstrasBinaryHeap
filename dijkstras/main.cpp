#include <iostream>
#include "BinaryHeap.h"
#include <vector>
#include <cstdint>
#include <limits>


const std::uint8_t threshold = 128;
struct Point {
    int x;
    int y;
};

using ProbMap = std::vector<std::vector<std::uint8_t>>;
using CostMap = std::vector<std::vector<double>>;

void dijkstras(ProbMap map, const Point start, const Point end) {
    CostMap score_map(map.size(), std::vector<double>(map[0].size(), std::numeric_limits<double>::infinity()));
    score_map[start.y][start.x] = 0;
        

}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}