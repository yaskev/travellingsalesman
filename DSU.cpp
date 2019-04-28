#include "DSU.h"
#include <vector>

using namespace std;

DSU::DSU(int count) {
    parent = vector<int>(count, -1);
    for( int i = 0; i < count; ++i )
        parent[i] = i;
    rank = vector<int>(count, 1);
}

void DSU::combine(int set1, int set2) {
    int s1 = findSet(set1);
    int s2 = findSet(set2);
    if( s1 != s2 ) {
        if( rank[s1] < rank[s2] )
            parent[s1] = s2;
        else
            parent[s2] = s1;
        rank[s1] += rank[s2];
    }
}

int DSU::findSet(int elem) {
    if( parent[elem] != elem )
        parent[elem] = findSet(parent[elem]);
    return parent[elem];
}
