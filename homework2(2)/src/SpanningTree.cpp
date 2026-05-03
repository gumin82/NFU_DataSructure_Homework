//41343133
#include <iostream>
#include <vector>
using namespace std;

void DFS(int v, vector<vector<int>>& adj, vector<bool>& visited){
    visited[v]=true;

    for(int u: adj[v]){
        if(!visited[u]){
            cout<<v<<" - "<<u<<endl;
            DFS(u,adj,visited);
        }
    }
}

int main(){
    int V,E;
    cin>>V>>E;

    vector<vector<int>> adj(V);

    for(int i=0;i<E;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<bool> visited(V,false);

    cout<<"Spanning Tree edges:\n";
    DFS(0,adj,visited);
}
