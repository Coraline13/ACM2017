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


static const int MAX_DIST = 1000000;

struct edge_t {
    int node, color;
};

struct dij_t {
    int dist, node;
};

bool lowestColor(const edge_t& e1, const edge_t& e2) {
    return e1.color < e2.color;
}

bool sameNode(const edge_t& e1, const edge_t& e2) {
    return e1.node == e2.node;
}

bool operator<(const dij_t& d1, const dij_t& d2) {
    return d1.dist < d2.dist;
}

typedef std::vector<std::vector<edge_t>> graph_t;

int compareTrails(const std::vector<edge_t>& nodeTrail, int node1, int node2) {
    bool firstSmaller = false;
    bool equal = true;
    while (node1 != node2) {
        const edge_t& prev1 = nodeTrail[node1], prev2 = nodeTrail[node2];
        firstSmaller = prev1.color < prev2.color;
        equal &= prev1.color == prev2.color;
        node1 = prev1.node;
        node2 = prev2.node;
    }

    return equal ? 0 : (firstSmaller ? -1 : 1);
}

void idealPaths(const graph_t& graph, int source,
                std::vector<int>& distanceFromSource, std::vector<edge_t>& nodeTrail) {
    std::priority_queue<dij_t> nodesToTry;
    std::vector<char> visited(graph.size());

    distanceFromSource[source] = 0;
    nodesToTry.push({ 0, source });
    nodeTrail[source] = { source, 0 };
    visited[source] = true;

    while (!nodesToTry.empty()) {
        dij_t step = nodesToTry.top();
        nodesToTry.pop();
        visited[step.node] = true;

        for (const edge_t& edge : graph[step.node]) {

            int maybe = distanceFromSource[step.node] + 1;
            bool better = distanceFromSource[edge.node] > maybe;
            if (distanceFromSource[edge.node] == maybe) {
                const edge_t& prevStep = nodeTrail[edge.node];
                int trailCmp = compareTrails(nodeTrail, step.node, prevStep.node);
                better = trailCmp < 0 || (trailCmp == 0 && edge.color < prevStep.color);
            }
            if (better) {
                distanceFromSource[edge.node] = distanceFromSource[step.node] + 1;
                nodeTrail[edge.node] = { step.node, edge.color };
            }

            if (!visited[edge.node]) {
                nodesToTry.push({ distanceFromSource[edge.node], edge.node });
            }
        }
    }
}

int main() {
    int nRooms, nEdges;
#ifndef __LOCAL
    std::istream& input = std::cin;
    std::ostream& output = std::cout;
#else
    std::ifstream inTest("tests/labyrinth.in");
    std::istream& input = inTest;
    std::ostream& output = std::cout;
#endif

    input >> nRooms >> nEdges;
    graph_t graph((unsigned long) (nRooms + 1));

    for (int e = 1; e <= nEdges; ++e) {
        int n1, n2, c;
        input >> n1 >> n2 >> c;
        graph[n1].push_back({ n2, c });
        graph[n2].push_back({ n1, c });
    }

    for (int n = 0; n < nRooms; ++n) {
        std::sort(graph[n].begin(), graph[n].end(), lowestColor);
        auto new_end = std::unique(graph[n].begin(), graph[n].end(), sameNode);
        graph[n].erase(new_end, graph[n].end());
    }


    std::vector<int> distanceFromSource(graph.size(), MAX_DIST);
    std::vector<edge_t> nodeTrail(graph.size());
    idealPaths(graph, 1, distanceFromSource, nodeTrail);

    std::vector<int> idealPath;
    idealPath.reserve((unsigned long) distanceFromSource[nRooms]);

    int prevNode = nRooms;
    while (prevNode != 1) {
        idealPath.push_back(nodeTrail[prevNode].color);
        prevNode = nodeTrail[prevNode].node;
    }

    output << idealPath.size() << '\n';
    for (int i = (int) (idealPath.size() - 1); i >= 0; --i) {
        output << idealPath[i] << " ";
    }

    output << '\n';
    output.flush();
    return 0;
}
