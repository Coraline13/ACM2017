#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>


inline void writeSolution(std::ostream& output, int t, int solution) {
    output << "Case " << t << ": " << solution << '\n';
}

#define FAIL(output, t) { writeSolution(output, -1); continue; }
#define SUCCESS(output, t, sol) { writeSolution(output, sol); continue; }


int getLongestLeap(const std::vector<int>& segmentLengths) {
    if (segmentLengths.size() == 1) {
        return segmentLengths[0];
    }

    if (segmentLengths.size() == 2) {
        return segmentLengths[0] + segmentLengths[1];
    }

    int longest = -1;
    int evenSeg = 0, oddSeg = 0;
    for (int i = 0; i < segmentLengths.size(); ++i) {
        int segment = segmentLengths[i];
        evenSeg += segment;
        oddSeg += segment;
        if (i % 2 == 0) {
            longest = std::max(longest, evenSeg);
            evenSeg = 0;
        }
        else {
            longest = std::max(longest, oddSeg);
            oddSeg = 0;
        }
    }

    if (evenSeg > 0) {
        longest = std::max(longest, evenSeg);
    }
    if (oddSeg > 0) {
        longest = std::max(longest, oddSeg);
    }

    return longest;
}

int main() {
    std::string source, target;
    int nTests;
#ifndef __LOCAL
    std::istream& input = std::cin;
    std::ostream& output = std::cout;
#else
    std::ifstream inTest("tests/frog.in");
    std::istream& input = inTest;
    std::ostream& output = std::cout;
#endif

    input >> nTests;

    std::vector<int> segmentLengths;
    for (int t = 1; t <= nTests; ++t) {
        int nStones, totalDistance, prevDist = 0;
        int longestLeap = -1;
        input >> nStones >> totalDistance;
        segmentLengths.clear();

        for (int s = 0; s < nStones; ++s) {
            char S;
            input >> S;
            bool bigStone = S == 'B';
            int dist;
            input >> S >> dist;

            segmentLengths.push_back(dist - prevDist);
            prevDist = dist;
            if (bigStone) {
                longestLeap = std::max(longestLeap, getLongestLeap(segmentLengths));
                segmentLengths.clear();
            }
        }
        segmentLengths.push_back(totalDistance - prevDist);
        longestLeap = std::max(longestLeap, getLongestLeap(segmentLengths));
        writeSolution(output, t, longestLeap);
    }

    output.flush();
    return 0;
}
