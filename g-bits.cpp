#include <iostream>
#include <string>
#include <fstream>
#include <vector>


inline void writeSolution(std::ostream& output, int t, int solution) {
    output << "Case " << t << ": " << solution << '\n';
}


int main() {
    std::string source, target;
    int nTests;
#ifndef __LOCAL
    std::istream& input = std::cin;
    std::ostream& output = std::cout;
#else
    std::ifstream inTest("tests/bits.in");
    std::istream& input = inTest;
    std::ostream& output = std::cout;
#endif

    input >> nTests;

    output << nTests << std::endl;
    for (int t = 1; t <= nTests; ++t) {
        int oneToZero = 0, zeroToOne = 0, totalWildcards = 0, oneWildcards = 0, targetZeroes = 0, sourceZeroes = 0;
        int nOps = 0;
        input >> source >> target;
        if (source.length() != target.length()) {
            writeSolution(output, t, -1);
            continue;
        }

        for (int i = 0; i < source.length(); ++i) {
            if (source[i] != target[i]) {
                switch (source[i]) {
                    case '0':
                        zeroToOne++;
                        break;
                    case '1':
                        oneToZero++; break;
                    case '?':
                        totalWildcards++;
                        oneWildcards += (target[i] == '1' ? 1 : 0);
                        break;
                    default:
                        break;
                }
            }
            sourceZeroes += (source[i] == '0' ? 1 : 0);
            targetZeroes += (target[i] == '0' ? 1 : 0);
        }

        if (targetZeroes > sourceZeroes + totalWildcards) {
            // too many zeroes required
            writeSolution(output, t, -1);
            continue;
        }

        // all 1 <-> 0 swaps (solve 2 problems in one op)
        nOps += std::min(zeroToOne, oneToZero);
        if (zeroToOne > oneToZero) {
            // swap all zeros to ones
            nOps += zeroToOne - oneToZero;
        }
        else if (oneToZero > zeroToOne) {
            int nSwaps = oneToZero - zeroToOne;
            // swap all remaining ones with wildcards above zero
            if (oneWildcards < nSwaps) {
                // if there are not enough wildcards above zeroes, the target cannot be reached
                writeSolution(output, t, -1);
                continue;
            }

            nOps += nSwaps;
        }

        // set all wildcards to whatever is necessary
        nOps += totalWildcards;
        writeSolution(output, t, nOps);
    }

    output.flush();
    return 0;
}
