//41343122
#include <iostream>
using namespace std;

int main(){
    int V,E;
    cin>>V>>E;

    int unweighted[100][100]={0};
    int weighted[100][100];

    //初始化weighted=-1沒有邊
    for(int i=0;i<V;i++)
        for(int j=0;j<V;j++)
            weighted[i][j] = -1;

    for(int i=0;i<E;i++){
        int u,v,w;
        cin>>u>>v>>w;

        //無權重
        unweighted[u][v]=1;
        unweighted[v][u]=1;

        //有權重
        weighted[u][v]=w;
        weighted[v][u]=w;
    }

    cout<<"無權重\n";
    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++)
            cout<<unweighted[i][j]<<" ";
        cout<<endl;
    }

    cout<<"\n有權重:\n";
    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            if(weighted[i][j]==-1) cout<<"0 ";
            else cout<<weighted[i][j]<<" ";
        }
        cout<<endl;
    }
}
