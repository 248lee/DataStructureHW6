#include <bits/stdc++.h>
#include "graph.h"
using namespace std;

int main()
{
    bool is_di;
    cout << "Enter the mode of your graph. NON-Directed = 0, Directed = 1: ";
    cin >> is_di;
    int n;
    cout << "How many vertices do you have in this graph: ";
    cin >> n;
    Graph gh;
    cout << "Enter the data of your vertices:\n";
    for (int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        gh.InsertVertex(tmp);
    }

    int e;
    cout << "How many edges do you have in this graph (support multigraph). Notice that you're graph is a " << (is_di ? "Directed Graph" : "NON-Directed Graph") << ": ";
    cin >> e;
    cout << "Input the edges of your vertices (support multigraph) in the format \"start end weight\":\n";
    for (int i = 0; i < e; i++)
    {
        int u, v, tmp;
        cin >> u >> v >> tmp;
        gh.InsertEdge(u, v, tmp);
        if (!is_di)
            gh.InsertEdge(v, u, tmp);
    }

    int start;
    cout << "Now find the shortest path. Please enter the start vertex: ";
    cin >> start;
    vector<pair<int, int> > v = gh.ShortestPath(start);
    for (int i = 0; i < v.size(); i++)
    {
        cout << start << ", " << v[i].second << ", " << v[i].first << '\n';
    }
    cout << "\n";

    vector<pair<pair<int, int>, int> > minspantree = gh.MinSpanTree();
    cout << "Below is a minimum spanning tree of this graph:\n";
    int sum = 0;
    for (int i = 0; i < minspantree.size(); i++)
    {
        cout << minspantree[i].first.first << ", " << minspantree[i].first.second << ": " << minspantree[i].second << "\n";
        sum += minspantree[i].second;
    }
    cout << "Total weight: " << sum << "\n";
    return 0;
}