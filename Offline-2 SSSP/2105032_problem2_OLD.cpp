#include <bits/stdc++.h>
#include "vertex.cpp"
using namespace std;

class Edge
{
    vertex *u;
    vertex *v;
    int wt;

public:
    Edge(vertex *u, vertex *v, int wt)
    {
        this->u = u;
        this->v = v;
        this->wt = wt;
    }
    vertex *getU() { return this->u; }
    vertex *getV() { return this->v; }
    int getWt() { return this->wt; }

    void setWt(int wt) { this->wt = wt; }
};

bool BellManFord(vector<Edge> &edges, int V, int s, vector<vertex *> &graph)    // O(VE)
{
    for (int i = 0; i < V; i++)
    {
        graph[i]->setDistance(INF);
    }
    graph[s]->setDistance(0);
    for (int i = 0; i < V - 1; i++)
    {
        for (auto it : edges)
        {
            vertex *u = it.getU();
            vertex *v = it.getV();
            int wt = it.getWt();

            if (u->getDistance() != INF && u->getDistance() + wt < v->getDistance())
            {
                v->setDistance(u->getDistance() + wt);
            }
        }
    }

    for (auto it : edges)
    {
        vertex *u = it.getU();
        vertex *v = it.getV();
        int wt = it.getWt();

        if (u->getDistance() != INF && u->getDistance() + wt < v->getDistance())
        {
            return false;
        }
    }
    return true;
}

int main()
{
    vector<Edge> edges;
    vector<vertex *> graph; // for tracking vertices

    int V, E;
    cin >> V >> E;

    for (int i = 0; i < V; i++)
    {
        graph.push_back(new vertex(i));
    }

    int s, d, w;
    for (int i = 0; i < E; i++)
    {
        cin >> s >> d >> w;
        s--, d--;

        edges.push_back(Edge(graph[s], graph[d], w));
    }

    int edgeSource, edgeDest, rangeMin, rangeMax;

    cin >> edgeSource >> edgeDest;

    cin >> rangeMin >> rangeMax;

    int source, destination;
    cin >> source >> destination;
    source--, destination--;

    BellManFord(edges, V, source, graph);
    int initialDist = graph[destination]->getDistance();

    edgeSource--, edgeDest--;
    Edge edge = Edge(graph[edgeSource], graph[edgeDest], 0);
    edges.push_back(edge);

    pair<int, int> mini = {initialDist, 0};
    bool isPossible = false;
    for (int i = rangeMin; i <= rangeMax; i++)
    {
        edges[E].setWt(i);
        if (BellManFord(edges, V, source, graph))
        {
            if (graph[destination]->getDistance() < mini.first)
            {
                mini = {graph[destination]->getDistance(), i};
                isPossible = true;
            }
        }
    }
    if (isPossible)
        cout << mini.second << " " << mini.first << endl;
    else
        cout << "impossible" << endl;

    return 0;
}
/*
4 4
1 2 10
2 3 10
1 4 20
4 2 30
4 3
-50 50
1 3

ans: -50 -30

5 6
1 2 1
2 3 2
3 5 1
3 4 2
4 5 5
1 4 3
4 2
-10 5
1 5

ans: -4 2

4 4
1 2 10
2 3 10
1 4 20
4 2 30
4 3
1 20
1 3

ans: impossible

4 4
1 2 10
2 3 10
1 4 20
4 2 30
4 3
-1 20
1 3

ans: -1 19

5 6
1 2 1
2 3 -3
3 5 1
3 4 -3
4 5 5
1 4 3
4 2
-10 5
1 5

ans:impossible

4 4
1 2 10
2 3 10
1 4 20
4 2 30
4 3
1 20
4 3

ans:1 1
*/