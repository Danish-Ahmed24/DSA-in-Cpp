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

        void bfs(int startNode){
            queue<int> q;
            unordered_map<int , bool> visited;

            q.push(startNode);
            while(!q.empty()){
                int node = q.front();
                cout<<node<<" ";
                visited[node]=true;
                q.pop();
                for(auto i:adjList[node]){
                    if(!visited[i]){
                        q.push(i);
                        visited[i]=true;
                    }
                }
            }
            
        }
    };


int main()
{
    Graph g;
    g.addUnDirectedEdge(1,2);
    g.addUnDirectedEdge(2,4);
    g.addUnDirectedEdge(2,3);
    g.addUnDirectedEdge(3,6);
    g.addUnDirectedEdge(3,5);

    g.bfs(1);
}