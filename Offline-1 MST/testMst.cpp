#include <bits/stdc++.h>
#include "vertex.cpp"
const long long INF = 1000;
int minWt = 1e5;
// vector<vertex *> graph;

template <typename T>
void printVct(vector<T> a)
{
    for (int i = 0; i < a.size(); i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}

int prim(int E, int V, vector<vertex *> &graph)
{
    vector<int> key(V + 1);
    vector<bool> mst(V + 1);
    vector<int> parent(V + 1);

    for (int i = 0; i < V; i++)
    {
        key[i] = INF;
        mst[i] = false;
        parent[i] = -1;
    }

    int uIndex = 0;
    key[uIndex] = 0;
    mst[uIndex] = true;

    for (int i = 0; i < V; i++)
    {
        int mini = INF;

        for (int i = 0; i < V; i++)
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
bool isValid(vector<pair<pair<vertex *, vertex *>, int>> currentCombination, int m)
{
    vector<bool> isVisited(m, false);
    vector<int> parent(m, -1);

    vector<vertex *> subGraph;
    for (int i = 0; i < m; i++)
    {
        subGraph.push_back(new vertex(i));
    }

    for (int i = 0; i < currentCombination.size(); i++)
    {
        int s, d, w;
        s = currentCombination[i].first.first->getIndex();
        d = currentCombination[i].first.second->getIndex();
        w = currentCombination[i].second;

        subGraph[s]->addEdge(subGraph[d], w);
        subGraph[d]->addEdge(subGraph[s], w);
    }

    isVisited[0] = true;
    queue<vertex *> Q;
    vertex *v;
    Q.push(subGraph[0]);
    while (!Q.empty())
    {
        vertex *u = Q.front();
        Q.pop();
        for (int i = 0; i < u->getSize(); i++)
        {
            vertex *v = u->getAdj(i).first;
            if (!isVisited[v->getIndex()])
            {
                isVisited[v->getIndex()] = true;
                parent[v->getIndex()] = u->getIndex();
                Q.push(v);
            }
            else if (parent[u->getIndex()] != v->getIndex())
            {
                return false;
            }
        }
    }

    for (auto i : isVisited)
    {
        if (!i)
            return false;
    }
    return true;
}

int countSet(int mask)
{
    int count = 0;
    while (mask > 0)
    {
        count += (mask & 1);
        mask = mask >> 1;
    }
    return count;
}

int secondBest(vector<pair<pair<vertex *, vertex *>, int>> &edges, int index, int m)
{
    vector<vertex *> subGraph;
    for (int i = 0; i < m; i++)
    {
        subGraph.push_back(new vertex(i));
    }
    for (int i = 0; i < edges.size(); i++)
    {
        if (i == index)
            continue;
        int s, d, w;
        s = edges[i].first.first->getIndex();
        d = edges[i].first.second->getIndex();
        w = edges[i].second;

        subGraph[s]->addEdge(subGraph[d], w);
        subGraph[d]->addEdge(subGraph[s], w);
    }
    return prim(edges.size() - 1,m, subGraph);
}
void getCombination(vector<pair<pair<vertex *, vertex *>, int>> &edges, int E, int m, int minWt) // E-> number of edges in mst (V(m)-1)
{   //m= total edges
    int count = 0;
    for (int mask = 0; mask < (1 << m); mask++)
    {
        if (countSet(mask) == E)
        {
            // cout << countSet(mask) << endl;
            vector<pair<pair<vertex *, vertex *>, int>> currentCombination;
            for (int i = 0; i < m; i++)
            {
                if (mask & (1 << i))
                {
                    currentCombination.push_back(edges[i]);
                }
            }
            int sum = 0;
            for (int i = 0; i < currentCombination.size(); i++)
            {
                sum += currentCombination[i].second;
            }

            if (sum == minWt)
            {
                if (isValid(currentCombination, E + 1))
                {
                    int sec = INF;
                    for (int i = 0; i < currentCombination.size(); i++)
                    {
                        for (int j = 0; j < edges.size(); j++)
                        {
                            if (edges[j].first.first->getIndex() == currentCombination[i].first.first->getIndex() && edges[j].first.second->getIndex() == currentCombination[i].first.second->getIndex() && edges[j].second == currentCombination[i].second)
                            {
                                int temp = secondBest(edges, j, E+1);
                                if (temp < sec && temp > minWt)
                                    sec = temp;
                            }
                        }
                    }
                    cout << minWt<<"\n"<<sec << endl;
                    return;
                    // cout << count + 1 << ": [";
                    // for (int i = 0; i < currentCombination.size(); i++)
                    // {
                    //     cout << "[" << currentCombination[i].first.first->getIndex() << ", " << currentCombination[i].first.second->getIndex() << ", " << currentCombination[i].second << "]";
                    //     if (i != currentCombination.size() - 1)
                    //         cout << ", ";
                    // }
                    // cout << "]" << endl;
                    // count++;
                }
            }
        }
    }
}
int main()
{
    vector<vertex *> graph;
    int V, E;
    // double q;
    cin >> V >> E; // m == Edges number

    vector<pair<pair<vertex *, vertex *>, int>> edges;
    // n as Vertices and m as Edges
    for (int i = 0; i < V; i++)
    {
        graph.push_back(new vertex(i));
    }

    int s, d, w;
    for (int i = 0; i < E; i++)
    {
        cin >> s >> d >> w;
        graph[s]->addEdge(graph[d], w);
        graph[d]->addEdge(graph[s], w);
        edges.push_back(make_pair(make_pair(graph[s], graph[d]), w));
    }

    minWt = prim(E, V, graph);
    // cout << "MSTs: " << endl;
    getCombination(edges, V - 1, E, minWt);
    // cout << minWt + q << endl;
}
/*
5 10
0 1 1
2 4 1
1 2 2
0 4 2
3 4 3
0 3 5
1 4 6
2 3 8
0 2 9
1 3 9

MSTs:
1 : [[0, 1, 1], [2, 4, 1], [1, 2, 2], [3, 4, 3]]
2 : [[0, 1, 1], [2, 4, 1], [0, 4, 2], [3, 4, 3]]

7 12
3 4 1
1 5 1
1 4 1
0 6 4
2 3 8
4 5 8
2 6 10
0 5 10
3 6 10
1 6 10
1 3 12
3 5 12

MSTs:
1 : [[3, 4, 1], [1, 5, 1], [1, 4, 1], [0, 6, 4], [2, 3, 8], [2, 6, 10]]
2 : [[3, 4, 1], [1, 5, 1], [1, 4, 1], [0, 6, 4], [2, 3, 8], [0, 5, 10]]
3 : [[3, 4, 1], [1, 5, 1], [1, 4, 1], [0, 6, 4], [2, 3, 8], [3, 6, 10]]
4 : [[3, 4, 1], [1, 5, 1], [1, 4, 1], [0, 6, 4], [2, 3, 8], [1, 6, 10]]
*/