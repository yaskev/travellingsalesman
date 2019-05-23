# Travelling salesman problem
### Description
This is the implementation of a well-known travelling salesman problem.

The program approximates the length of the path covering all vertices using either:
1) 2-approximation (The weight of the minimum spanning tree built on the given complete graph. Kruskal's algorithm and Disjoint Set Union are used)
2) 1.5-approximation (The weight of the Euler loop on the given graph. Again Kruskal and exhaustive search on vertices with odd degrees)

Tests are run several times (number specified by the user), the mean and the standard deviation of the ratio precise/approx is computed

The range of the vertices number, the number of tests and the kind of approximation (2 or 1.5) is set in input.txt
