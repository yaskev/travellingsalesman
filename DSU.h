#ifndef TSP_DSU_H
#define TSP_DSU_H

#include <vector>

class DSU {
public:
    explicit DSU(int count);
    void combine(int, int);
    int findSet(int elem); // recursively calculate for parent
private:
    std::vector<int> parent;
    std::vector<int> rank;
};


#endif //TSP_DSU_H
