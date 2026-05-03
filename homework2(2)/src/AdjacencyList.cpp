//41343122
#include <iostream>
#include <vector>
using namespace std;

int main(){
    int V,E;
    cin>>V>>E;

    vector<vector<int>> unweighted(V);
    vector<vector<pair<int,int>>> weighted(V);

    for(int i=0;i<E;i++){
        int u,v,w;
        cin>>u>>v>>w;

        unweighted[u].push_back(v);
        unweighted[v].push_back(u);

        weighted[u].push_back({v,w});
        weighted[v].push_back({u,w});
    }

    cout<<"無權重:\n";
    for(int i=0;i<V;i++){
        cout<<i<<": ";
        for(int x: unweighted[i])
            cout<<x<<" ";
        cout<<endl;
    }

    cout<<"\n有權重:\n";
    for(int i=0;i<V;i++){
        cout<<i<<": ";
        for(auto x: weighted[i])
            cout<<"("<<x.first<<","<<x.second<<") ";
        cout<<endl;
    }
}
