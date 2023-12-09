/*
#include <bits/stdc++.h>
#include "vertex.cpp"

using namespace std;

class Graph
{
    vector<vertex *> graph;

public:
    void addVertex(vertex *v)
    {
        graph.push_back(v);
    }

    void primMST()
    {
        // Initialize MST set
        vector<vertex *> mstSet;

        // Set key values to infinity for all vertices
        for (auto v : graph)
        {
            v->setDistance(INT_MAX);
        }

        // Choose any vertex as the starting point
        vertex *startVertex = graph[0];
        startVertex->setDistance(0);

        // Repeat until all vertices are included in MST
        while (mstSet.size() < graph.size())
        {
            // Find the vertex with the minimum key value
            vertex *minVertex = nullptr;
            for (auto v : graph)
            {
                if (find(mstSet.begin(), mstSet.end(), v) == mstSet.end() &&
                    (minVertex == nullptr || v->getDistance() < minVertex->getDistance()))
                {
                    minVertex = v;
                }
            }

            // Add the minVertex to MST set
            mstSet.push_back(minVertex);

            // Update key values of adjacent vertices
            for (int i = 0; i < minVertex->getSize(); ++i)
            {
                vertex *adjVertex = minVertex->getAdj(i);
                int weight = 1; // Assuming unweighted graph, modify as needed

                if (find(mstSet.begin(), mstSet.end(), adjVertex) == mstSet.end() &&
                    weight < adjVertex->getDistance())
                {
                    adjVertex->setDistance(weight);
                    adjVertex->setParent(minVertex);
                }
            }
        }

        // Print MST
        cout << "Minimum Spanning Tree:\n";
        for (auto v : mstSet)
        {
            if (v->getParent() != nullptr)
            {
                cout << v->getParent()->getIndex() << " - " << v->getIndex() << endl;
            }
        }
    }
};

int main()
{
    // Create a graph
    Graph g;

    // Create vertices
    vertex *v1 = new vertex(0);
    vertex *v2 = new vertex(1);
    vertex *v3 = new vertex(2);

    // Add vertices to the graph
    g.addVertex(v1);
    g.addVertex(v2);
    g.addVertex(v3);
    
    // Add edges (connections between vertices)
    v1->addEdge(v2);
    v1->addEdge(v3);
    v2->addEdge(v3);

    // Perform Prim's algorithm to find MST
    g.primMST();

    return 0;
}
*/

/*
void edgeCombinations(int index, int mstEdge, vector<pair<int, pair<int, int>>> &graph, 
    set<vector<pair<int, pair<int, int>>>> &combinatons, vector<pair<int, pair<int, int>>> &trees)
{
    if (mstEdge == 0)
    {
        combinatons.insert(trees);
    }

    if (index >= graph.size())
    {
        return;
    }

    trees.push_back(graph[index]);
    edgeCombinations(index + 1, mstEdge - 1, graph, combinatons, trees);
    trees.pop_back();
    edgeCombinations(index + 1, mstEdge, graph, combinatons, trees);
}

set<vector<pair<int, pair<int, int>>>> allPossibleGraphCombinations(vector<pair<int, pair<int, int>>> &graph, int mstEdge, int mstWeight)
{
    set<vector<pair<int, pair<int, int>>>> mstCombinations;
    set<vector<pair<int, pair<int, int>>>> combinations;
    vector<pair<int, pair<int, int>>> trees;
    edgeCombinations(0, mstEdge, graph, combinations, trees);
    for (auto &combination : combinations)
    {
        int totalWeight = weight(combination);
        if (totalWeight > mstWeight)
        {
            continue;
        }
        mstCombinations.insert(combination);
    }
    return mstCombinations;
}
*/

/*
#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int src, dest, weight;
};

void generateCombinations(vector<Edge>& edges) {
    int n = edges.size();

    for (int mask = 0; mask < (1 << n); ++mask) {
        vector<Edge> currentCombination;

        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                currentCombination.push_back(edges[i]);
            }
        }

        // Process the current combination (currentCombination vector)
        cout << "Combination: ";
        for (Edge edge : currentCombination) {
            cout << "(" << edge.src << "," << edge.dest << ") ";
        }
        cout << endl;
    }
}

int main() {
    vector<Edge> edges = {{0, 1, 2}, {1, 2, 3}, {1, 3, 4}, {2, 4, 5}};

    generateCombinations(edges);

    return 0;
}

*/

/*
#include <iostream>
#include <vector>

using namespace std;

class Edge {
public:
    int src, dest, weight;

    Edge(int src, int dest, int weight) : src(src), dest(dest), weight(weight) {}
};

void generateCombinations(vector<Edge>& edges, int n, int m) {
    for (int mask = 0; mask < (1 << m); ++mask) {
        // Count the number of set bits in the mask
        int count = __builtin_popcount(mask);

        if (count == n) {
            vector<Edge> currentCombination;

            for (int i = 0; i < m; ++i) {
                if (mask & (1 << i)) {
                    currentCombination.push_back(edges[i]);
                }
            }

            // Process the current combination
            cout << "Combination: ";
            for (Edge edge : currentCombination) {
                cout << "(" << edge.src << "," << edge.dest << ") ";
            }
            cout << endl;
        }
    }
}

int main() {
    int n = 2;  // Number of edges in each combination
    int m = 4;  // Total number of edges in the tree

    // Example edges (src, dest, weight)
    vector<Edge> edges = { {0, 1, 2}, {1, 2, 3}, {1, 3, 4}, {2, 4, 5} };

    generateCombinations(edges, n, m);

    return 0;
}

*/