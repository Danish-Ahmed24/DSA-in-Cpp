#include<iostream>
#include<map>
#include<unordered_map>
#include<list>
using namespace std;

class Graph{
    public:
        unordered_map<int,list<pair<int,int>>> adjList;
        
    void addWeightedEdge(int u,int v,int w){
        adjList[u].push_back({v,w});
        adjList[v].push_back({u,w});
    }

    //ye khod kario oye
    void dijkstra(int src){
        
    }
};

int main()
{

    return 0;
}