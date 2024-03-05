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
    int a,jobs;
    cin>>a>>jobs;

    vector<vertex *> graph;

    for(int i=0;i<jobs+a+2;i++)
    {
        graph.push_back(new vertex(i));
    }

    int t; 
    int job; 
    int cnt; 

    for(int i=0;i<jobs;i++)
    {


        char c = 'x';
        scanf("%d%c",&job,&c);
        while(c!='\n')
        {

            scanf("%d%c",&t,&c);
            // if(c=='\n') break;
            graph[job]->addEdge(graph[t+jobs],1);
        }
        // cin>>job;//job_no

        //# format 1 1 2 -1 -- -1 as terminating condition
        // for(int j=0;j<a;j++)
        // {
        //     cin>>t;
        //     if(t==-1)   break;
        //     graph[job]->addEdge(graph[t+jobs],1);
        // }

        // char s[100];

        // cout<<endl;

        // cin.getline(s,10);
        // cout<<s<<endl;

        //# format 1 2 1 2 -- 2 as number of eleme`nts
        // cin>>cnt;
        // for(int k=0;k<cnt;k++)
        // {
        //     cin>>t;
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

    // for(auto i: graph)
    // {
    //     cout<<i->getIndex()<<" -> ";
    //     i->printAdj();

    //     cout<<endl;
    // }

    minCut(graph, 0, jobs + a + 1, flowOut);
    for(auto i:graph)   delete i;

    return 0;
}

/*
4 3
1 1 2
2 3
3 3 4

3 3
1
2 3
3 1 2


3 3
1 -1
2 3 -1
3 1 2 -1


4 3
1 2 1 2 
2 1 3 
3 2 3 4 

3 3
1 0
2 1 3 
3 2 1 2

*/