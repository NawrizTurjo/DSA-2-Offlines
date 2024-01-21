#include <bits/stdc++.h>
#include "vertex.cpp"
using namespace std;
int V;

bool bfs(vector<vertex *> &graph, int s, int t)
{
    for (auto i : graph)
    {
        i->setColor(WHITE);
        i->setParent(i, 0);
    }
    queue<vertex *> q;
    q.push(graph[s]);
    graph[s]->setColor(GRAY);
    while (!q.empty())
    {
        vertex *u = q.front();
        q.pop();

        for (int i = 0; i < u->getSize(); i++)
        {
            vertex *v = u->getAdj(i).first;
            int wt = u->getAdj(i).second;
            if (v->getColor() == WHITE && wt > 0)
            {
                v->setParent(u, wt);
                v->setColor(GRAY);
                q.push(v);
            }
        }
        u->setColor(BLACK);
    }

    return graph[t]->getColor();
}
void minCut(vector<vertex *> &graph, int s, int t, vector<int> &flowOut)
{
    while (bfs(graph, s, t))
    {
        int flow = INT_MAX;
        for (int i = t; i != s; i = graph[i]->getParent().first->getIndex())
        {
            vertex *u = graph[i]->getParent().first;
            int wt = graph[i]->getParent().second;
            flow = min(flow, wt);
        }

        for (int v = t; v != s; v = graph[v]->getParent().first->getIndex())
        {
            vertex *u = graph[v]->getParent().first;
            u->setAdj(graph[v], flow, '-');
            graph[v]->setAdj(u, flow, '+');
        }

        for (int v = t; v != s; v = graph[v]->getParent().first->getIndex())
        {
            vertex *u = graph[v]->getParent().first;
            int wt = graph[v]->getParent().second;
            flowOut[u->getIndex()] += flow;
        }
    }
    cout << flowOut[0] << endl;
}
int main()
{
    // int V1, V2;
    // cin >> V1 >> V2;

    // int V = V1 + V2 + 2;

    // vector<tuple<int, int, int>> male, female;
    // int h, a, d;
    // for (int i = 0; i < V1; i++)
    // {
    //     cin >> h >> a >> d;
    //     male.push_back({h, a, d});
    // }
    // for (int i = 0; i < V2; i++)
    // {
    //     cin >> h >> a >> d;
    //     female.push_back({h, a, d});
    // }
    // vector<vertex *> graph;
    // for (int i = 0; i < V1 + V2 + 2; i++)
    // {
    //     graph.push_back(new vertex(i));
    // }

    // for (int i = 0; i < V1; i++)
    // {
    //     for (int j = 0; j < V2; j++)
    //     {
    //         int hDiff = abs(get<0>(male[i]) - get<0>(female[j]));
    //         int aDiff = abs(get<1>(male[i]) - get<1>(female[j]));
    //         bool dDiff = (get<2>(male[i]) == get<2>(female[j]));

    //         if (hDiff <= 10 && aDiff <= 5 && dDiff)
    //         {
    //             graph[i + 1]->addEdge(graph[V1 + 1 + j], 1);
    //         }
    //     }
    // }

    // for (int i = 0; i < V1; i++)
    // {
    //     graph[0]->addEdge(graph[i + 1], 1);
    // }

    // vector<int> flowOut(V1 + V2 + 2, 0);

    // for (int i = 0; i < V2; i++)
    // {
    //     graph[V1 + i + 1]->addEdge(graph[V1 + V2 + 1], 1);
    // }

    // minCut(graph, 0, V1 + V2 + 1, flowOut);
    // for(auto i:graph)   delete i;

    int a,jobs;
    cin>>a>>jobs;

    vector<vertex *> graph;

    for(int i=0;i<jobs+a+2;i++)
    {
        graph.push_back(new vertex(i));
    }

    int t; 
    int job; 

    for(int i=0;i<jobs;i++)
    {
        cin>>job;//job_no

        char c;
        int a;

        c='x';

        while(c!='\n')
        {
            scanf("%d%c",&t,&c);

            if(c=='\n') break;
            graph[job]->addEdge(graph[t+jobs],1);
        }

        // for(int j=0;j<a;j++)
        // {
        //     cin>>t;
        //     if(t==-1)   break;
        //     graph[job]->addEdge(graph[t+jobs],1);
        // }
        
    }

    
    
    for (int i = 0; i < jobs; i++)
    {
        graph[0]->addEdge(graph[i + 1], 1);
    }

    vector<int> flowOut(jobs + a + 2, 0);

    for (int i = 0; i < a; i++)
    {
        graph[jobs + i + 1]->addEdge(graph[jobs + a + 1], 1);
    }

    for(auto i: graph)
    {
        cout<<i->getIndex()<<" -> ";
        i->printAdj();

        cout<<endl;
    }

    minCut(graph, 0, jobs + a + 1, flowOut);
    for(auto i:graph)   delete i;

    return 0;
}

