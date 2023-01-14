To compile this file, enter these commands in the cmd in Windows:

g++ main.cpp -o main.exe
.\main.exe


For linux, enter these commands:

g++ main.cpp -o main
./main

For developers who want to include "graph.h" into your C++ code, make sure to put graph.h and List.h in the same directories of your code.

---------------------------------------------------------------------------------------------------------------------------------------------------
Documentation:

Class:

Graph


Constructor:

Graph(): Create an empty doubly linked circular list.


Public methods:

CircularList<T>:

void InsertVertex(int v): Insert a vertex with its data be "v" in the graph.

void InsertEdge(int u, int v, int weight): Add an edge from u to v with weight.

vector<pair<int, int> > ShortestPath(int v): Return the shortest path from the vertex v to all  the vertices in the graph. The result is stored in a vector where its element represents "distance" and "destination".

vector<pair<pair<int, int>, int> > Graph::MinSpanTree(): Return the edges of a minimum spanning tree. The edges are stored in a vector where its element represents "from", "to", and "weight".
