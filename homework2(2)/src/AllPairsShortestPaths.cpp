//41343122
#include <iostream>
using namespace std;

int main(){
    int V;
    cin >> V;

    int dist[100][100];

    for(int i=0;i<V;i++)
        for(int j=0;j<V;j++)
            cin >> dist[i][j];

    for(int k=0;k<V;k++)
        for(int i=0;i<V;i++)
            for(int j=0;j<V;j++)
                if(dist[i][k]+dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k]+dist[k][j];

    cout<<"Result:\n";
    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++)
            cout<<dist[i][j]<<" ";
        cout<<endl;
    }
}
