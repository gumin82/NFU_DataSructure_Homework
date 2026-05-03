//41343133
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main(){
    int V,E;
    cin >> V >> E;

    vector<vector<pair<int,int>>> adj(V);

    for(int i=0;i<E;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back(make_pair(v,w));
        adj[v].push_back(make_pair(u,w));
    }

    vector<bool> visited(V,false);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    pq.push(make_pair(0,0)); // (weight, node)
    int cost=0;
    int count=0;

    while(!pq.empty()){
        pair<int,int> top = pq.top();
        pq.pop();

        int w = top.first;
        int u = top.second;

        if(visited[u]) continue;

        visited[u] = true;
        cost += w;
        count++;

        for(int i=0;i<adj[u].size();i++){
            int v = adj[u][i].first;
            int wt = adj[u][i].second;

            if(!visited[v]){
                pq.push(make_pair(wt,v));
            }
        }
    }

    if(count != V)
        cout<<"Graph is not connected\n";
    else
        cout<<"Total cost: "<<cost<<endl;
}
