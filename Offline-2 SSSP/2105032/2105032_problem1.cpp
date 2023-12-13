#include <bits/stdc++.h>
#include "vertex.cpp"
using namespace std;
int djikstra(int s, int d, vector<vertex *> &graph) // O(ElogV) V = N*(C+1) AND E = M+C*N
{
    graph[s]->setDistance(0);
    graph[s]->setColor(GRAY);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push({graph[s]->getDistance(), s});
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();

        if (graph[u]->getColor() == BLACK)
            continue;

        graph[u]->setColor(BLACK);
        for (int i = 0; i < graph[u]->getSize(); i++)
        {
            vertex *v = graph[u]->getAdj(i).first;
            int wt = graph[u]->getAdj(i).second;

            if (graph[u]->getDistance() != INF && graph[u]->getDistance() + wt < v->getDistance())
            {
                v->setDistance(graph[u]->getDistance() + wt);
                v->setParent(graph[u]);
                if (v->getColor() != BLACK)
                {
                    v->setColor(GRAY);
                    q.push({v->getDistance(), v->getIndex()});
                }
            }
        }
    }

    if (graph[d]->getColor() == BLACK)
    {
        return graph[d]->getDistance();
    }
    else
        return -1;
}
int main()
{
    int V, E, maxCapacity;
    cin >> V >> E >> maxCapacity;

    vector<vertex *> graph;
    for (int i = 0; i < V * (maxCapacity + 1); i++)
    {
        graph.push_back(new vertex(i));
    }

    vector<int> costs;
    for (int i = 0; i < V; i++)
    {
        int temp;
        cin >> temp;
        costs.push_back(temp);
    }

    int index = 0, innerIndex = 0;
    for (int i = 0; i < V; i++)
    {
        for (int j = 1; j <= maxCapacity; j++)
        {
            graph[innerIndex++]->addEdge(graph[index + j], costs[i]);
        }
        innerIndex++;
        index += (maxCapacity + 1);
    }

    int s, d, wt;
    for (int i = 0; i < E; i++)
    {
        cin >> s >> d >> wt;
        s--, d--; // to maintain 0 based indexing
        if (wt > maxCapacity)
            continue;

        int VertexMainS = (maxCapacity + 1) * s;
        int VertexMainD = (maxCapacity + 1) * d;

        int LastMainS = (maxCapacity + 1) * s + maxCapacity;
        int LastMainD = (maxCapacity + 1) * d + maxCapacity;

        // s->d
        for (int i = LastMainS; i >= VertexMainS; i--)
        {
            if (i - VertexMainS >= wt)
            {
                graph[i]->addEdge(graph[VertexMainD + (i - VertexMainS - wt)], 0);
            }
        }

        // d->s
        for (int i = LastMainD; i >= VertexMainD; i--)
        {
            if (i - VertexMainD >= wt)
            {
                graph[i]->addEdge(graph[VertexMainS + (i - VertexMainD - wt)], 0);
            }
        }
    }

    int source, destination;
    cin >> source >> destination;

    int ans = djikstra((source - 1) * (maxCapacity + 1), (destination - 1) * (maxCapacity + 1), graph);
    if (ans != -1)
    {
        cout << ans << endl;
    }
    else
        cout << "impossible" << endl;

    return 0;
}
/*
4 4 3
11 12 13 14
1 2 2
2 4 1
3 4 4
1 3 3
1 4

5 5 10
10 10 20 12 13
1 2 9
1 3 8
2 3 1
2 4 11
3 4 7
1 4

4 4 8
10 12 11 13
1 2 5
1 3 11
2 4 12
3 4 7
1 4
*/
