//
// Created by Alexander on 28.04.2019.
//

#ifndef TSP_LISTGRAPH_H
#define TSP_LISTGRAPH_H

#include <vector>

using namespace std;

class ListGraph {
public:
    ~ListGraph() = default;
    explicit ListGraph(int);
    void AddEdge(int from, int to, double weight);
    void RemoveEdge(int from, int to);
    double Weight(int from, int to) const;
    int VerticesCount() const { return static_cast<int>(toList.size()); }
    vector<pair<double, int>> GetNextVertices(int vertex) const { return toList[vertex]; }
private:
    vector<vector<pair<double, int>>> toList;
};


#endif //TSP_LISTGRAPH_H
