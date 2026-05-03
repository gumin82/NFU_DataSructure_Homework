//41343133
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int V, E;
    cin >> V >> E;

    vector<vector<pair<int, int>>> adj(V);

    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back(make_pair(v, w));
    }

    int start;
    cin >> start;

    vector<int> dist(V, 1000000000); // INF
    dist[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(0, start)); // (distance, node)

    while (!pq.empty()) {
        pair<int, int> top = pq.top();
        pq.pop();

        int d = top.first;
        int u = top.second;

        if (d > dist[u]) continue;

        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].first;
            int w = adj[u][i].second;

            if (dist[v] > d + w) {
                dist[v] = d + w;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    for (int i = 0; i < V; i++)
        cout << "dist[" << i << "]=" << dist[i] << endl;
}
