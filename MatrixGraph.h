#ifndef TSP_MATRIXGRAPH_H
#define TSP_MATRIXGRAPH_H

#include <vector>

using namespace std;

class MatrixGraph {
public:
    ~MatrixGraph()  = default;
    explicit MatrixGraph(int vertNumber);
    void AddEdge(int from, int to, double weight);
    int VerticesCount() const { return static_cast<int>(adjTable.size()); }
    double Weight(int from, int to) const { return adjTable[from][to]; }
    vector<double> GetNextVertices(int vertex) const;
    vector<double> GetPrevVertices(int vertex) const;
private:
    vector<vector<double>> adjTable;
};


#endif //TSP_MATRIXGRAPH_H
