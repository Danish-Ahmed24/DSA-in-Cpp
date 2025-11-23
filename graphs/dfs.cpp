#include<iostream>
#include<map>
#include<set>
#include<list>
#include<queue>
#include<unordered_map>

using namespace std;

class Graph {
    public:
        unordered_map<int ,list<int>> adjList;
        
        void addUnDirectedEdge(int u,int v){
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }
        
        void addDirectedEdge(int u,int v){
            adjList[u].push_back(v);
        }

        void dfs(int startNode,unordered_map<int,bool> &visited){
            cout<<startNode<<" ";
            visited[startNode]=true;
            for(auto i:adjList[startNode]){
                if(!visited[i]){
                    dfs(i,visited);
                }
            }
        }
    };


int main()
{
    Graph g;
    // g.addUnDirectedEdge(1,2);
    // g.addUnDirectedEdge(2,4);
    // g.addUnDirectedEdge(2,3);
    // g.addUnDirectedEdge(3,6);
    // g.addUnDirectedEdge(3,5);


    g.addUnDirectedEdge(0,4);
    g.addUnDirectedEdge(4,1);
    g.addUnDirectedEdge(4,2);
    g.addUnDirectedEdge(1,5);
    g.addUnDirectedEdge(2,3);
    g.addUnDirectedEdge(5,3);

    unordered_map<int,bool> visited;
    g.dfs(0, visited);

}