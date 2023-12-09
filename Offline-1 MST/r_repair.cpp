#include <bits/stdc++.h>
using namespace std;

const int N = 100;
int parent[N];
int SIZE[N];

void make(int v) {
    parent[v] = v;
    SIZE[v] = 1;
}

int find(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find(parent[v]);
}

void Union(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) {
        if (SIZE[a] < SIZE[b]) {
            swap(a, b);
        }
        parent[b] = a;
        SIZE[a] += SIZE[b];
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        make(i);
    }

    int components = n;
    int largestComponent = 1;

    for (int day = 1; day <= m; day++) {
        int u, v;
        cin >> u >> v;

        if (find(u) != find(v)) {
            components--;
            int sizeU = SIZE[find(u)];
            int sizeV = SIZE[find(v)];
            Union(u, v);

            int newSize = sizeU + sizeV;
            largestComponent = max(largestComponent, newSize);
        }

        cout << components << " " << largestComponent << "\n";
    }

    return 0;
}
/*
5 3
1 2
1 3
4 5
*/
