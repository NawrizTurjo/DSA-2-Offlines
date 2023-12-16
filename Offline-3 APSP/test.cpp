//{ Driver Code Starts
// Initial Template for C++

#include <bits/stdc++.h>
using namespace std;
#define INF 1000000
// } Driver Code Ends
// User function Template for C++
class Solution
{
public:
    int findCity(int n, int m, vector<vector<int>> &edges,int distanceThreshold)
    {
        vector<vector<int>> distance(n, vector<int>(n, INF));
        for (int i = 0; i < n; i++)
        {
            distance[i][i] = 0;
        }
        for (auto i : edges)
        {
            int u = i[0];
            int v = i[1];
            int w = i[2];
            // u--,v--;
            distance[u][v] = w;
            distance[v][u] = w;
        }
        for (int k = 0; k < n; k++)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (distance[i][k] != INF && distance[k][j] != INF)
                    {
                        distance[i][j] = min(distance[i][j], distance[i][k] + distance[k][j]);
                    }
                }
            }
        }
        vector<int> costs(n, 0);
        int mini = INF;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (distance[i][j] <= distanceThreshold && i != j)
                {
                    costs[i]++;
                }
            }
            if (costs[i] < mini)
                mini = costs[i];
        }

        for (int i = n - 1; i >= 0; i--)
            if (costs[i] == mini)
            {
                return i;
            }
            return -1;
    }
};

//{ Driver Code Starts.
int main()
{
    int t=1;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> adj;
        // n--;
        for (int i = 0; i < m; ++i)
        {
            vector<int> temp;
            for (int j = 0; j < 3; ++j)
            {
                int x;
                cin >> x;
                temp.push_back(x);
            }
            adj.push_back(temp);
        }

        int dist;
        cin >> dist;
        Solution obj;
        cout << obj.findCity(n, m, adj, dist) << "\n";
    }
}

// } Driver Code Ends