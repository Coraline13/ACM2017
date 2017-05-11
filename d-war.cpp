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


int main() {
#ifndef __LOCAL
    std::istream& input = std::cin;
    std::ostream& output = std::cout;
#else
    std::ifstream inTest("tests/war.in");
    std::istream& input = inTest;
    std::ostream& output = std::cout;
#endif

    int nPeople;
    input >> nPeople;

    std::vector<std::pair<int, int>> galeti((unsigned long) nPeople);
    for (int i = 0; i < nPeople; ++i) {
       galeti[i] = { i, i };
    }

    int c, x, y;
    do {
        input >> c >> x >> y;
        if (c == 0) {
            break;
        }

        switch (c) {
            case 1:
            {
                bool areEnemies = galeti[x].second == galeti[y].second;
                if (areEnemies) {
                    output << -1 << "\n";
                    break;
                }
                int galeata = galeti[y].first;
                for (int i = 0; i < nPeople; ++i) {
                    if (galeti[i].first == galeata) {
                        galeti[i].first = galeti[x].first;
                        galeti[i].second = galeti[x].second;
                    }
                }
                break;
            }

            case 2:
            {
                bool areEnemies = galeti[x].first == galeti[y].first;
                if (areEnemies) {
                    output << -1 << "\n";
                    break;
                }
                int galeata = galeti[y].second;
                for (int i = 0; i < nPeople; ++i) {
                    if (galeti[i].second == galeata) {
                        galeti[i].first = galeti[x].first;
                        galeti[i].second = galeti[x].second;
                    }
                }
                break;
            }

            case 3: {

                bool areEnemies = galeti[x].first == galeti[y].first;
                output << (areEnemies ? 1 : 0) << "\n";
                break;
            }

            case 4: {

                bool areEnemies = galeti[x].second == galeti[y].second;
                output << (areEnemies ? 1 : 0) << "\n";
                break;
            }

        }
    } while (c != 0);

    output.flush();
    return 0;
}
