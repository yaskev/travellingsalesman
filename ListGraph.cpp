#include "ListGraph.h"

ListGraph::ListGraph(int vertNumber) {
    for( int i = 0; i < vertNumber; ++i )
        toList.emplace_back();
}

void ListGraph::AddEdge(int from, int to, double weight) {
    toList[from].emplace_back(weight, to);
}

void ListGraph::RemoveEdge(int from, int to) {
    for( int i = 0; i < toList[from].size(); ++i ) {
        if( toList[from][i].second == to ) {
            toList[from].erase(toList[from].begin() + i);
            break;
        }
    }
}

double ListGraph::Weight(int from, int to) const {
    for( const auto& elem : toList[from] ) {
        if( elem.second == to )
            return elem.first;
    }

    return -1;
}