#include <bits/stdc++.h>
using namespace std;
#define INF 1000000
int main()
{
    int V, E;
    cin >> V >> E;

    vector<vector<int>> distance(V, vector<int>(V, INF));
    for (int i = 0; i < V; i++)
    {
        distance[i][i] = 0;
    }

    int u, v, w;
    for (int i = 0; i < E; i++)
    {
        cin >> u >> v >> w;
        u--, v--;
        distance[u][v] = w;
        distance[v][u] = w;
    }

    int cost;
    cin >> cost;

    for (int k = 0; k < V; k++)
    {
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                if (distance[i][k] != INF && distance[k][j] != INF)
                    distance[i][j] = min(distance[i][j], distance[i][k] + distance[k][j]);
            }
        }
    }

    vector<int> costs(V, 0);
    int mini = INF;

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (distance[i][j] <= cost && i != j)
            {
                costs[i]++;
            }
        }
        if (costs[i] < mini)
            mini = costs[i];
    }

    for (int i = 0; i < V; i++)
        if (costs[i] == mini)
            cout << i + 1 << " ";
    return 0;
}
/*
4 4
1 2 3
2 3 1
2 4 4
3 4 1
4

4 6
1 2 8
1 4 1
2 3 1
3 1 4
4 2 2
4 3 9
4

4 6
1 2 8
1 4 1
2 3 1
3 1 4
4 2 2
4 3 9
5
*/