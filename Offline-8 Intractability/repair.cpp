#include <bits/stdc++.h>
using namespace std;

#define INF INT_MAX
#define vi vector<int>
#define REP(i, n) for (int i = 0; i < (n); i++)

const int MAX_N = 1005;
const int MAX_V = 100005;
int dp[MAX_N][MAX_V];
vector<vector<bool>> selected;

int knapsack(int idx, int rem_capacity, const vi &value, const vi &weight)
{
    if (idx == 0 || rem_capacity == 0)
        return 0;

    if (dp[idx][rem_capacity] != -1)
        return dp[idx][rem_capacity];

    int take = 0, leave = 0;
    if (rem_capacity >= value[idx - 1])
        take = knapsack(idx - 1, rem_capacity - value[idx - 1], value, weight) + weight[idx - 1];
    leave = knapsack(idx - 1, rem_capacity, value, weight);

    if (take >= leave)
    {
        selected[idx][rem_capacity] = true;
        return dp[idx][rem_capacity] = take;
    }
    else
    {
        selected[idx][rem_capacity] = false;
        return dp[idx][rem_capacity] = leave;
    }
}

void reconstruct(int idx, int capacity, const vi &value, const vi &weight)
{
    int taken_weight = 0;
    for (int i = idx; i >= 1; i--)
    {
        if (selected[i][capacity])
        {
            cout << i << " ";
            taken_weight += weight[i - 1];
            capacity -= value[i - 1];
        }
    }
    cout << endl;
    cout << taken_weight << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    memset(dp, -1, sizeof(dp));
    freopen("in.txt", "r", stdin);

    int capacity, n;
    cin >> n >> capacity;
    vi value(n), weight(n);
    selected.resize(n + 1, vector<bool>(capacity + 1, false));

    REP(i, n)
        cin >> value[i] >> weight[i];

    cout << knapsack(n, capacity, value, weight) << endl;
    reconstruct(n, capacity, value, weight);

    return 0;
}
