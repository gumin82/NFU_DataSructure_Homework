//41343133
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, w;
};

int parent[100];

int find(int x){
    if(parent[x]==x) return x;
    return parent[x]=find(parent[x]);
}

void unite(int a,int b){
    parent[find(a)] = find(b);
}

bool cmp(Edge a, Edge b){
    return a.w < b.w;
}

int main(){
    int V,E;
    cin >> V >> E;

    vector<Edge> edges(E);
    for(int i=0;i<E;i++)
        cin >> edges[i].u >> edges[i].v >> edges[i].w;

    for(int i=0;i<V;i++) parent[i]=i;

    sort(edges.begin(), edges.end(), cmp);

    int cost=0;
    cout<<"MST edges:\n";

    for(auto e: edges){
        if(find(e.u)!=find(e.v)){
            unite(e.u,e.v);
            cout<<e.u<<"-"<<e.v<<" ("<<e.w<<")\n";
            cost+=e.w;
        }
    }

    cout<<"Total cost: "<<cost<<endl;
}
