#include<iostream>
#include<map>
#include<unordered_map>
#include<list>
using namespace std;

class Graph {
    public:
        unordered_map<int , list<int>> adj;

    void addEdge(int u,int v , bool direction){
        //directed if direction == 1 else vice versa

        adj[u].push_back(v);
        
        if(!direction){
            adj[v].push_back(u);
        }

    }

    void printAdjList(){
        for(auto i:adj){
            cout<<i.first<<" -> ";
            for(auto j:i.second){
                cout<<j<<",";
            }
            cout<<endl;
        }
    }
};


int main()
{
    int n,m;
   
    cout<<"no of nodes: ";
    cin>>n;
    
    cout<<"no of edges: ";
    cin>>m;

    Graph g;
    for(int i=0; i < m; i++){
        int u,v;
        cin>>u>>v;
        //creating undirected graphs
        g.addEdge(u,v,0);
    }

    g.printAdjList();
}