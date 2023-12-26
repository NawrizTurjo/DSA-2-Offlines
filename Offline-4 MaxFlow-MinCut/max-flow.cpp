#include <bits/stdc++.h>
#include "vertex.cpp"
using namespace std;
int V;

bool bfs(vector<vertex *> &graph, int s, int t)
{
    for (auto i : graph)
    {
        i->setColor(WHITE);
        i->setParent(i, 0);
    }
    queue<vertex *> q;
    q.push(graph[s]);
    graph[s]->setColor(GRAY);
    while (!q.empty())
    {
        vertex *u = q.front();
        q.pop();

        for (int i = 0; i < u->getSize(); i++)
        {
            vertex *v = u->getAdj(i).first;
            int wt = u->getAdj(i).second;
            if (v->getColor() == WHITE && wt > 0)
            {
                v->setParent(u, wt);
                v->setColor(GRAY);
                q.push(v);
            }
        }
        u->setColor(BLACK);
    }

    return graph[t]->getColor();
}
vector<vector<int>> vertices;
int vIndex = -1;
void dfsVisit(vector<vertex *> &graph, vertex *u)
{
    u->setColor(GRAY);

    for (int i = 0; i < u->getSize(); i++)
    {
        vertex *v = u->getAdj(i).first;
        int wt = u->getAdj(i).second;

        if (v->getColor() == WHITE && wt > 0)
        {
            dfsVisit(graph, v);
        }
    }
    u->setColor(BLACK);
    vertices[vIndex].push_back(u->getIndex());
}
void dfs(vector<vertex *> graph, int s)
{
    for (auto i : graph)
    {
        i->setColor(WHITE);
    }

    for (int i = 1; i <= V; i++)
    {
        if (graph[i]->getColor() == WHITE)
        {
            vIndex++;
            vertices.push_back(vector<int>());
            dfsVisit(graph, graph[i]);
        }
    }
    cout << "[";
    for (int i = 0; i < vertices.size(); i++)
    {
        cout << "{";
        sort(vertices[i].begin(), vertices[i].end());
        for (int j = 0; j < vertices[i].size(); j++)
        {
            cout << vertices[i][j];
            if (j != vertices[i].size() - 1)
                cout << ",";
        }
        cout << "}";
        if (i != vertices.size() - 1)
            cout << ",";
    }
    cout << "]";
}
void minCut(vector<vertex *> &graph, int s, int t, vector<int> &flowOut)
{
    while (bfs(graph, s, t))
    {
        int flow = INT_MAX;
        for (int i = t; i != s; i = graph[i]->getParent().first->getIndex())
        {
            vertex *u = graph[i]->getParent().first;
            int wt = graph[i]->getParent().second;
            flow = min(flow, wt);
        }

        for (int v = t; v != s; v = graph[v]->getParent().first->getIndex())
        {
            vertex *u = graph[v]->getParent().first;
            u->setAdj(graph[v], flow, '-');
            graph[v]->setAdj(u, flow, '+');
        }

        for (int v = t; v != s; v = graph[v]->getParent().first->getIndex())
        {
            vertex *u = graph[v]->getParent().first;
            int wt = graph[v]->getParent().second;
            flowOut[u->getIndex()] += flow;
            // cout << u->getIndex() << endl;
            // cout << flowOut[u->getIndex()] << endl;
        }
    }
    int maxi = INT_MIN;
    int index = 0;
    for (int i = 1; i <= V; i++)
    {
        if (flowOut[i] > maxi && i != s && i != t)
        {
            maxi = flowOut[i];
            index = i;
        }
    }
    cout << index << " " << maxi << endl;
    dfs(graph, s);
}
int main()
{
    int E;
    cin >> V >> E;

    vector<vertex *> graph;
    for (int i = 0; i <= V; i++)
    {
        graph.push_back(new vertex(i));
    }

    int u, v, cap;
    for (int i = 0; i < E; i++)
    {
        cin >> u >> v >> cap;
        graph[u]->addEdge(graph[v], cap);
    }

    int s, t;
    cin >> s >> t;

    vector<int> flowOut(V + 1, 0);

    minCut(graph, s, t, flowOut);
    for(auto i:graph)   delete i;
    return 0;
}