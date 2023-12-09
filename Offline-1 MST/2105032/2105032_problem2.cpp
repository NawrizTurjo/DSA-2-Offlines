#include <bits/stdc++.h>
#include "vertex.cpp"
const long long INF = 1000;
int minWt = 1e5;
vector<vertex *> graph;

template <typename T>
void printVct(vector<T> a)
{
    for (int i = 0; i < a.size(); i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}

int prim(int m, int n)
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

    for(auto i:isVisited)
    {
        if(!i)  return false;
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
void getCombination(vector<pair<pair<vertex *, vertex *>, int>> &edges, int E, int m, int minWt) // E-> number of edges in mst (V(m)-1)
{
    vector<pair<pair<vertex *, vertex *>, int>> totalCombinations;
    int count = 0;
    for (int mask = 0; mask < (1 << m); mask++)
    {
        if (countSet(mask) == E)
        {
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
                if (isValid(currentCombination, E+1))
                {
                    for(auto curr:currentCombination)
                    {
                        totalCombinations.push_back(curr);
                    }
                    count++;
                }
            }
        }
    }
    vector<int> numCombinations(m,0);
    int index = 0;
    for(auto combination : edges)
    {
        for(auto curr:totalCombinations)
        {
            if(combination.first.first->getIndex()==curr.first.first->getIndex() && combination.first.second->getIndex()==curr.first.second->getIndex() && combination.second==curr.second)
            {
                numCombinations[index]++;
            }
        }
        index++;
    }

    for(auto i:numCombinations)
    {
        if(i==0)    cout<<"none"<<endl;
        else if(i==count)   cout<<"any"<<endl;
        else cout<<"at least one"<<endl;
    }
    // cout << count << endl;
}
int main()
{
    // vector<vertex *> graph;
    int n, m;
    cin >> n >> m;

    vector<pair<pair<vertex *, vertex *>, int>> edges;
    // n as Vertices and m as Edges
    for (int i = 0; i < n; i++)
    {
        graph.push_back(new vertex(i));
    }

    int s, d, w;
    for (int i = 0; i < m; i++)
    {
        cin >> s >> d >> w;
        graph[s-1]->addEdge(graph[d-1], w);
        graph[d-1]->addEdge(graph[s-1], w);
        edges.push_back(make_pair(make_pair(graph[s-1], graph[d-1]), w));
    }

    minWt = prim(m, n);
    getCombination(edges, n - 1, m, minWt);
}
/*
4 5
1 2 101
1 3 100
2 3 2
2 4 2
3 4 1

3 3
1 2 1
2 3 1
1 3 2
*/