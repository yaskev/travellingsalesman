#include "MatrixGraph.h"
#include "ListGraph.h"
#include "DSU.h"

#include <fstream>
#include <set>
#include <random>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <stack>

typedef unsigned long long int ulong;

double MSTCost(const set<pair<double, pair<int, int>>>& edges) {
    double totalWeight = 0;
    DSU dsu(static_cast<int>(edges.size()));
    for( auto next : edges ) {
        if( dsu.findSet(next.second.first) != dsu.findSet(next.second.second) ) {
            totalWeight += 2 * next.first;
            dsu.combine(next.second.first, next.second.second);
        }
    }

    return totalWeight;
}

vector<int> getOddVertices(const ListGraph& mst) {
    vector<int> result;
    for( int i = 0; i < mst.VerticesCount(); ++i ) {
        if( mst.GetNextVertices(i).size() % 2 )
            result.push_back(i);
    }

    return result;
}

double eulerCycleWeight(const ListGraph& graph) {
    ListGraph tmp = graph;
    vector<int> path;
    stack<int> st({0});
    while( !st.empty() ) {
        int current = st.top();
        auto next = tmp.GetNextVertices(current);
        if( next.empty() ) {
            path.insert(path.begin(), current);
            st.pop();
        }
        else {
            st.push(next[0].second);
            tmp.RemoveEdge(current, next[0].second);
            tmp.RemoveEdge(next[0].second, current);
        }
    }
    double cycleWeight = 0;
    for( int i = 0; i < path.size() - 1; ++i ) {
        cycleWeight += graph.Weight(path[i], path[i+1]);
    }

    return cycleWeight;
}

double OptimizedMSTCost(const MatrixGraph& graph, const set<pair<double, pair<int, int>>>& edges) {
    double minWeight = INT32_MAX;
    ListGraph mst(graph.VerticesCount());
    DSU dsu(mst.VerticesCount());

    // Build MST using Kruskal Algorithm
    for( auto next : edges ) {
        if( dsu.findSet(next.second.first) != dsu.findSet(next.second.second) ) {
            mst.AddEdge(next.second.first, next.second.second, next.first);
            mst.AddEdge(next.second.second, next.second.first, next.first);
            dsu.combine(next.second.first, next.second.second);
        }
    }
    vector<int> oddVertices = getOddVertices(mst);
    set<vector<set<int>>> used;
    while( next_permutation(oddVertices.begin(), oddVertices.end()) ) {
        vector<set<int>> tmp;
        for( int i = 0; i < oddVertices.size(); i += 2 )
            tmp.push_back(set<int>({oddVertices[i], oddVertices[i+1]}));
        if( used.find(tmp) == used.end() ) {
            used.insert(tmp);
            for( const auto& new_pair : tmp) {
                int from = *new_pair.begin();
                int to = *(++new_pair.begin());
                double weight = graph.Weight(from, to);
                mst.AddEdge(from, to, weight);
                mst.AddEdge(to, from, weight);
            }
            double weight = eulerCycleWeight(mst);
            if( weight < minWeight )
                minWeight = weight;
            for( const auto& new_pair : tmp) {
                int from = *new_pair.begin();
                int to = *(++new_pair.begin());
                mst.RemoveEdge(from, to);
                mst.RemoveEdge(to, from);
            }
        }
    }

    return minWeight;
}

// The cost of a salesman's path
double calcCost(const MatrixGraph& graph, const vector<int>& vertices) {
    double sum = graph.Weight(vertices[0], vertices[vertices.size() - 1]); // Last edge of the salesman
    for( int i = 0; i < vertices.size() - 1; ++i ) {
        sum += graph.Weight(vertices[i], vertices[i + 1]);
    }
    return sum;
}

double preciseCost(const MatrixGraph& graph) {
    vector<int> vertices(graph.VerticesCount());
    for( int i = 0; i < graph.VerticesCount(); ++i )
        vertices[i] = i;
    double min_cost = calcCost(graph, vertices);
    while( next_permutation(vertices.begin(), vertices.end()) ) {
        double cost = calcCost(graph, vertices);
        if( cost < min_cost )
            min_cost = cost;
    }

    return min_cost;
}

vector<vector<double>> approx(ulong N_min, ulong N_max, ulong tests_no, double mean, double stddev, bool precise) {
    std::default_random_engine gen;
    std::normal_distribution<double> d(mean, stddev);

    auto approximation = vector<vector<double>>(N_max - N_min + 1, vector<double>(tests_no, 0.0));

    // Compute data for each N
    for( int i = 0; i < N_max - N_min + 1; ++i ) {
        vector<pair<double, double>> vertices(N_min + i);
        MatrixGraph graph(N_min + i);
        set<pair<double, pair<int, int>>> edgeSet;

        // Carry out "tests_no" test
        for (int j = 0; j < tests_no; ++j) {
            edgeSet.clear();
            for (int k = 0; k < N_min + i; ++k)
                vertices[k] = make_pair(d(gen), d(gen));

            // Initialize Graph
            for (int k = 0; k < N_min + i; ++k) {
                for (int z = 0; z < N_min + i; ++z) {
                    double weight = sqrt(((vertices[k].first - vertices[z].first)
                                          * (vertices[k].first - vertices[z].first)
                                          + (vertices[k].second - vertices[z].second)
                                          * (vertices[k].second - vertices[z].second)));
                    graph.AddEdge(k, z, weight);
                    edgeSet.insert(make_pair(weight, make_pair(k, z)));
                }
            }
            approximation[i][j] = (precise ? OptimizedMSTCost(graph, edgeSet) : MSTCost(edgeSet)) / preciseCost(graph);
        }
    }
    return approximation;
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    ulong N_min = 0, N_max = 0, tests_no = 0;
    double mean = 5, stddev = 1, precision = 1.5;

    fin >> N_min >> N_max >> tests_no >> mean >> stddev >> precision;

    bool precise = false;
    if( precision < 1.9 ) precise = true;

    auto approximation = approx(N_min, N_max, tests_no, mean, stddev, precise);

    for( int i = 0; i < N_max - N_min + 1; ++i ) {
        fout << N_min + i << " V: ";
        for (int j = 0; j < tests_no; ++j)
            fout << setprecision(4) << approximation[i][j] << " ";
        fout << "\n";
    }

    fout << "\n";

    for( int i = 0; i < N_max - N_min + 1; ++i ) {
        double mean_ = 0;
        for( int j = 0; j < tests_no; ++j )
            mean_ += approximation[i][j];
        mean_ /= approximation[i].size();
        double stddev_ = 0;
        for( int j = 0; j < tests_no; ++j )
            stddev_ += (approximation[i][j] - mean_) * (approximation[i][j] - mean_);
        stddev_ = sqrt(stddev_ / approximation[i].size());
        fout << N_min + i << " V: mean=" << setprecision(4)
                << mean_ << "; StdDev=" << setprecision(4) << stddev_ << "\n";
    }

    fin.close();
    fout.close();

    return 0;
}
