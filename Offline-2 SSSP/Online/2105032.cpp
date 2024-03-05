#include<bits/stdc++.h>
#include"vertex.cpp"
using namespace std;
int djikstra(int s, int d, vector<vertex *> &graph) // O(V + ElogV) V = N*(C+1) AND E = M+C*N
{
    graph[s]->setDistance(0);
    graph[s]->setColor(GRAY);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push({graph[s]->getDistance(), s});
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();

        if (graph[u]->getColor() == BLACK)
            continue;

        graph[u]->setColor(BLACK);
        for (int i = 0; i < graph[u]->getSize(); i++)
        {
            vertex *v = graph[u]->getAdj(i).first;
            int wt = graph[u]->getAdj(i).second;

            if (graph[u]->getDistance() != INF && graph[u]->getDistance() + graph[u]->getWt() < v->getDistance())
            {
                v->setDistance(graph[u]->getDistance() + graph[u]->getWt());
                v->setParent(graph[u]);
                if (v->getColor() != BLACK)
                {
                    v->setColor(GRAY);
                    q.push({v->getDistance(), v->getIndex()});
                }
            }
        }
    }

    if (graph[d]->getColor() == BLACK)
    {
        return graph[d]->getDistance();
    }
    else
        return -1;
}
int main()
{
    int V,E;
    cin>>V>>E;

    vector<int>costs(V);
    vector<vertex *> graph;

    for(int i=0;i<V;i++)
    {
        int t;
        cin>>t;
        costs[i]=t;
        graph.push_back(new vertex(i,t));
    }

    for(int i=0;i<E;i++)
    {
        int s,d;
        cin>>s>>d;
        s--,d--;

        graph[s]->addEdge(graph[d],1);
        graph[d]->addEdge(graph[s],1);
    }
    djikstra(0,V-1,graph);
    int cost = 0;
    int dist=V-1;
    while(graph[dist]->getParent()->getIndex()!=dist)
    {
        cost+=costs[dist];
        dist=graph[dist]->getParent()->getIndex();
    }
    cout<<cost;
    return 0;
}
/*
3 2
5 10 15
1 2
2 3

6 9
5 5 15 10 10 7
1 2
2 3
3 5
5 4
4 1
2 4
2 5
5 6
3 6
*/