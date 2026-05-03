//41343122
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

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
    queue<int> q;

    q.push(0);
    visited[0]=true;

    cout<<"BFS: ";

    while(!q.empty()){
        int v=q.front(); q.pop();
        cout<<v<<" ";

        for(int u: adj[v]){
            if(!visited[u]){
                visited[u]=true;
                q.push(u);
            }
        }
    }
}
