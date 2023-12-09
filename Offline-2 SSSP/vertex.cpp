#include <bits/stdc++.h>
using namespace std;

#define WHITE 0
#define GRAY 1
#define BLACK 2

#define INF 1000000

class vertex
{
    vector<pair <vertex *,int>> adj;
    int color;
    int distance;
    int index;
    int wt;
    vertex *parent;

public:
    vertex(int index)
    {
        color = WHITE;
        distance = INF;
        this->index = index;
        parent = NULL;
        // wt = INF;
    }
    void sort(vector<pair <vertex *,int>> &vct)
    {
        pair<vertex *,int> t;
        for (int i = 0; i < vct.size() - 1; i++)
        {
            for (int j = i + 1; j < vct.size(); j++)
            {
                if ((vct[i].first->getIndex()) > (vct[j].first->getIndex()))
                {
                    t = vct[i];
                    vct[i] = vct[j];
                    vct[j] = t;
                }
            }
        }
    }
    int getColor()
    {
        return this->color;
    }
    void addEdge(vertex *destination,int wt)
    {
        adj.push_back(make_pair(destination,wt));
        sort(adj);
    }
    void setColor(int color)
    {
        this->color = color;
    }
    void setDistance(int distance = 0)
    {
        this->distance = distance;
    }
    int getSize()
    {
        return this->adj.size();
    }
    pair <vertex *,int> getAdj(int i)
    {
        return this->adj[i];
    }
    vector<pair<vertex *, int>> getAdj()
    {
        return this->adj;
    }
    int getDistance()
    {
        return this->distance;
    }
    int getIndex()
    {
        return index;
    }
    void setParent(vertex *v)
    {
        parent = v;
    }
    vertex *getParent()
    {
        return this->parent;
    }
    void printAdj()
    {
        for (int i = 0; i < adj.size(); i++)
        {
            cout << adj[i].first->getIndex() << " "<<adj[i].second<<" ";
        }
    }

    void printdist()
    {
        if(this->distance==INF) cout<<"INF";
        else cout<<this->distance;
    }
};
