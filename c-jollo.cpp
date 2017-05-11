#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>


inline void writeSolution(std::ostream& output, int solution) {
    output << solution << '\n';
}

#define FAIL(output) { writeSolution(output, -1); continue; }
#define SUCCESS(output, sol) { writeSolution(output, sol); continue; }


int score(int card, int his[3]) {
    if (card > his[2]) {
        return 3;
    }
    if (card > his[1]) {
        return 2;
    }
    if (card > his[0]) {
        return 1;
    }

    return 0;
}

int betterThan(int card, int his[3], int mine[2]) {
    bool good = false;
    while (!good && card <= 52) {
        card += 1;
        good = true;
        for (int c = 0; c < 2; ++c) {
            if (his[c] == card || mine[c] == card) {
                good = false;
            }
        }
        good = good && his[2] != card;
    }

    return card <= 52 ? card : - 1;
}

int main() {
    std::string source, target;
    int nTests;
#ifndef __LOCAL
    std::istream& input = std::cin;
    std::ostream& output = std::cout;
#else
    std::ifstream inTest("tests/jollo.in");
    std::istream& input = inTest;
    std::ostream& output = std::cout;
#endif

    for (int t = 1;; ++t) {
        int his[3], mine[2], myScores[2];
        input >> his[0] >> his[1] >> his[2] >> mine[0] >> mine[1];
        std::sort(his, his + 3);
        std::sort(mine, mine + 2);
        if (his[0] == 0) {
            break;
        }

        myScores[0] = score(mine[0], his);
        myScores[1] = score(mine[1], his);
        if (myScores[0] == 3) {
            SUCCESS(output, betterThan(0, mine, his));
        }
        if (myScores[0] == 2 && myScores[1] >= 2) {
            SUCCESS(output, betterThan(his[1], his, mine));
        }
        if (myScores[0] < 2 && myScores[1] == 3) {
            SUCCESS(output, betterThan(his[2], his, mine));
        }

        FAIL(output);
    }

    output.flush();
    return 0;
}
