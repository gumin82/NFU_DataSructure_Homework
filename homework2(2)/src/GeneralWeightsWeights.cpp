//41343133#include <iostream>
#include <vector>
using namespace std;

struct Edge{
    int u,v,w;
};

int main(){
    int V,E;
    cin>>V>>E;

    vector<Edge> edges(E);
    for(int i=0;i<E;i++)
        cin>>edges[i].u>>edges[i].v>>edges[i].w;

    int start;
    cin>>start;

    vector<int> dist(V,1e9);
    dist[start]=0;

    for(int i=0;i<V-1;i++){
        for(auto e: edges){
            if(dist[e.u]!=1e9 && dist[e.v] > dist[e.u]+e.w)
                dist[e.v]=dist[e.u]+e.w;
        }
    }

    for(int i=0;i<V;i++)
        cout<<"dist["<<i<<"]="<<dist[i]<<endl;
}
