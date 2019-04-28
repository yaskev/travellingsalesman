#include "MatrixGraph.h"
#include <vector>

using namespace std;

MatrixGraph::MatrixGraph(int vertNumber) {
    adjTable.reserve(vertNumber);
    for (int i = 0; i < vertNumber; ++i)
        adjTable.emplace_back(vertNumber);
}

void MatrixGraph::AddEdge(int from, int to, double weight) {
    adjTable[from][to] = weight;
}

vector<double> MatrixGraph::GetNextVertices(int vertex) const {
    return adjTable[vertex];
}

vector<double> MatrixGraph::GetPrevVertices(int vertex) const {
    return adjTable[vertex];
}
