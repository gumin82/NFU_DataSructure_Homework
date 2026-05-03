//41343122
#include <iostream>
using namespace std;

struct Edge{
    int ivex, jvex;
    int weight;
    Edge* ilink;
    Edge* jlink;
};

struct Vertex{
    Edge* first;
};

Vertex graph[100];

int main(){
    int V,E;
    cin>>V>>E;

    for(int i=0;i<V;i++)
        graph[i].first = NULL;

    for(int i=0;i<E;i++){
        int u,v,w;
        cin>>u>>v>>w;

        Edge* e = new Edge{u,v,w,NULL,NULL};

        // 插入u的串列
        e->ilink = graph[u].first;
        graph[u].first = e;

        // 插入v的串列
        e->jlink = graph[v].first;
        graph[v].first = e;
    }

    cout<<"沒權重:\n";
    for(int i=0;i<V;i++){
        cout<<i<<": ";
        Edge* p = graph[i].first;
        while(p){
            int neighbor = (p->ivex==i)? p->jvex : p->ivex;
            cout<<neighbor<<" ";
            p = (p->ivex==i)? p->ilink : p->jlink;
        }
        cout<<endl;
    }

    cout<<"\n有權重:\n";
    for(int i=0;i<V;i++){
        cout<<i<<": ";
        Edge* p = graph[i].first;
        while(p){
            int neighbor = (p->ivex==i)? p->jvex : p->ivex;
            cout<<"("<<neighbor<<","<<p->weight<<") ";
            p = (p->ivex==i)? p->ilink : p->jlink;
        }
        cout<<endl;
    }
}
