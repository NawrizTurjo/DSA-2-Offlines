#include <bits/stdc++.h>
using namespace std;

const int N = 100;
int parent[N];
int SIZE[N];
void make(int v)
{
    parent[v] = v;
    SIZE[v] = 1;
}
int find(int v)
{
    if (v == parent[v])
        return v;
    return parent[v] = find(parent[v]);
}
void Union(int a, int b)
{
    a = find(a);
    b = find(b);
    if (a != b)
    {
        if (SIZE[a] < SIZE[b])
        {
            swap(a, b);
        }
        parent[b] = a;
        SIZE[a]+=SIZE[b];
    }
}
int main()
{
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++)
    {
        make(i);
    }
    vector<pair<int,pair<int ,int>>> edges;
    for(int i=0;i<k;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        edges.push_back({w,{u,v}});
    }
    sort(edges.begin(),edges.end());

    int total_cost = 0;
    for(auto &edge : edges)
    {
        int wt = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;
        if(find(u)==find(v))    continue;
        Union(u,v);
        total_cost+=wt;
        cout<<u<<" "<<v<<endl;
    }
    cout<<total_cost<<endl;
}

// O(alpha(n)) --> Reverse Ackerman function (Amortized function)
/*
6 9
5 4 9
1 4 1
5 1 4
4 3 5
4 2 3
1 2 2
3 2 3
3 6 8
2 6 7

*/