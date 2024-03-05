#include <bits/stdc++.h>
#include "vertex.cpp"
const long long INF = 1000;
int minWt = 1e5;

template <typename T>
void printVct(vector<T> a)
{
    for (int i = 0; i < a.size(); i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}

int prim(int m, int n, vector<vertex *> &graph)
{
    vector<int> key(n + 1);
    vector<bool> mst(n + 1);
    vector<int> parent(n + 1);

    for (int i = 0; i < n; i++)
    {
        key[i] = INF;
        mst[i] = false;
        parent[i] = -1;
    }

    int uIndex = 0;
    key[uIndex] = 0;
    mst[uIndex] = true;

    for (int i = 0; i < n; i++)
    {
        int mini = INF;

        for (int i = 0; i < n; i++)
        {
            if (!mst[i] && key[i] < mini)
            {
                uIndex = i;
                mini = key[i];
            }
        }
        mst[uIndex] = true;

        auto adj = graph[uIndex]->getAdj();

        for (auto i : adj) // i is a pair of vertex * V and int wt
        {
            vertex *v = i.first;
            int wt = i.second;
            int vIndex = v->getIndex();
            if (!mst[vIndex] && wt < key[vIndex])
            {
                key[vIndex] = wt;
                parent[vIndex] = uIndex;
            }
        }
    }

    return accumulate(key.begin(), key.end(), 0ll);
}
int main()
{
    vector<vertex *> graph;
    int V, E;
    cin >> V >> E;
    for (int i = 0; i <= V; i++)
    {
        graph.push_back(new vertex(i));
    }

    int zero;
    for (int i = 0; i < V; i++)
    {
        cin >> zero;
        graph[0]->addEdge(graph[i + 1], zero);
        graph[i + 1]->addEdge(graph[0], zero);
    }
    int s, d, w;
    for (int i = 0; i < E; i++)
    {
        cin >> s >> d >> w;
        graph[s]->addEdge(graph[d], w);
        graph[d]->addEdge(graph[s], w);
    }

    cout << prim(E, V + 1, graph) << endl;
}
/*
4 2
1 4 4 4
1 4 2
1 2 1

3 3
5 5 5
1 2 80
1 3 20
2 3 90
*/