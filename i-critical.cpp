#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>


inline void writeSolution(std::ostream& output, int solution) {
    output << solution << '\n';
}

#define FAIL(output) { writeSolution(output, -1); continue; }
#define SUCCESS(output, sol) { writeSolution(output, sol); continue; }

inline long long dimComplete(long long nNodes) {
    if (nNodes <= 1) {
        return 0;
    }
    if (nNodes == 2) {
        return 1;
    }
    return nNodes * (nNodes - 1) / 2;
}

int main() {
#ifndef __LOCAL
    std::istream& input = std::cin;
    std::ostream& output = std::cout;
#else
    std::ifstream inTest("tests/critical.in");
    std::istream& input = inTest;
    std::ostream& output = std::cout;
#endif

    int nTests;
    input >> nTests;

    for (int t = 0; t < nTests; ++t) {
        long long nodes, edges;
        input >> nodes >> edges;

        long long biggestComplete = 0;
        while (edges - dimComplete(biggestComplete) >= nodes - biggestComplete) {
            biggestComplete += 1;
        }

        if (biggestComplete > 0) {
            biggestComplete -= 1;
        }

        long long nCritical = nodes - biggestComplete;
        if (biggestComplete == 0) {
            nCritical -= 1;
        }

        if (edges - dimComplete(biggestComplete) - (nodes - biggestComplete) > 0) {
            nCritical -=1;
        }

        output << nCritical << '\n';
    }

    output.flush();
    return 0;
}
