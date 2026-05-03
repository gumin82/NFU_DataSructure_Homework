#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main(){
    int V,E;
    cin>>V>>E;

    vector<vector<pair<int,int>>> adj(V);
    vector<int> indegree(V,0);

    for(int i=0;i<E;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back(make_pair(v,w));
        indegree[v]++;
    }

    vector<int> ve(V,0);
    queue<int> q;

    for(int i=0;i<V;i++)
        if(indegree[i]==0)
            q.push(i);

    while(!q.empty()){
        int u = q.front();
        q.pop();

        for(int i=0;i<adj[u].size();i++){
            int v = adj[u][i].first;
            int w = adj[u][i].second;

            if(ve[v] < ve[u] + w)
                ve[v] = ve[u] + w;

            indegree[v]--;
            if(indegree[v]==0)
                q.push(v);
        }
    }

    cout<<"Earliest time:\n";
    for(int i=0;i<V;i++)
        cout<<"v"<<i<<": "<<ve[i]<<endl;
}
