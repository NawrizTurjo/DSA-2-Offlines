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

bool BellmanFord(vector<Edge> &edges, int V, int s, vector<vertex *> &graph, int edgeSource, int edgeDest, int rangeMin, int rangeMax)
{
    for (int i = 0; i < V; i++)
    {
        graph[i]->setDistance(INT_MAX);
    }
    graph[s]->setDistance(0);

    // Run Bellman-Ford considering the additional edge
    for (int i = 0; i < V - 1; i++)
    {
        for (auto it : edges)
        {
            vertex *u = it.getU();
            vertex *v = it.getV();
            int wt = it.getWt();

            if (u->getDistance() != INT_MAX && u->getDistance() + wt < v->getDistance())
            {
                v->setDistance(u->getDistance() + wt);
            }
        }
    }
    edges.push_back(Edge(graph[edgeSource],graph[edgeDest],rangeMin));
    
    // Relax the additional edge within the specified range
    for (int i = rangeMin; i <= rangeMax; i++)
    {
        edges[V].setWt(i); // Update the weight of the additional edge
        vertex *u = edges[edgeSource].getU();
        vertex *v = edges[edgeDest].getV();
        int wt = edges[edgeDest].getWt();

        if (u->getDistance() != INT_MAX && u->getDistance() + wt < v->getDistance())
        {
            v->setDistance(u->getDistance() + wt);
        }
    }

    // Check for negative cycles
    for (auto it : edges)
    {
        vertex *u = it.getU();
        vertex *v = it.getV();
        int wt = it.getWt();

        if (u->getDistance() != INT_MAX && u->getDistance() + wt < v->getDistance())
        {
            return false;
        }
    }

    return true;
}

int main()
{
    vector<Edge> edges;
    vector<vertex *> graph;

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

    int edgeSource, edgeDest;
    int rangeMin, rangeMax;
    int source, destination;

    cin >> edgeSource >> edgeDest;
    edgeSource--,edgeDest--;
    cin >> rangeMin >> rangeMax;
    cin >> source >> destination;

    source--, destination--;

    // Run Bellman-Ford algorithm only once
    if (BellmanFord(edges, V, source, graph, edgeSource, edgeDest, rangeMin, rangeMax))
    {
        int resultWeight = graph[destination]->getDistance();
        if (resultWeight == INT_MAX)
        {
            cout << "impossible" << endl;
        }
        else
        {
            cout << edges[E].getWt() << " " << resultWeight << endl;
        }
    }
    else
    {
        cout << "impossible" << endl;
    }

    return 0;
}
