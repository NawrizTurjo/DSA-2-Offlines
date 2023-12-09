#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Edge {
    int to, cost;
};

int main() {
    int N, M, C;
    cin >> N >> M >> C;

    vector<vector<Edge>> graph(N + 1);
    vector<int> gasPrices(N + 1);

    for (int i = 1; i <= N; ++i) {
        cin >> gasPrices[i];
    }

    for (int i = 0; i < M; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    int S, D;
    cin >> S >> D;

    vector<int> minCost(N + 1, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    pq.push({0, S});
    minCost[S] = 0;

    while (!pq.empty()) {
        int cost = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (cost > minCost[u]) {
            continue;
        }

        for (const auto& edge : graph[u]) {
            int v = edge.to;
            int newCost = cost + edge.cost * gasPrices[u];

            if (newCost < minCost[v] && newCost <= C) {
                minCost[v] = newCost;
                pq.push({newCost, v});
            }
        }
    }

    if (minCost[D] == INT_MAX) {
        cout << "Impossible to reach destination." << endl;
    } else {
        cout << minCost[D] << endl;
    }

    return 0;
}
