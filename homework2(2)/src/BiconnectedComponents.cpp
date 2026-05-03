//41343122
#include <iostream>
#include <vector>
using namespace std;

int timer = 0;

void DFS(int v, int parent, vector<vector<int>>& adj,
    vector<int>& disc, vector<int>& low, vector<bool>& ap) {

    disc[v] = low[v] = ++timer;
    int children = 0;

    for (int u : adj[v]) {
        if (!disc[u]) {
            children++;
            DFS(u, v, adj, disc, low, ap);

            low[v] = min(low[v], low[u]);

            if (parent != -1 && low[u] >= disc[v])
                ap[v] = true;
        }
        else if (u != parent)
            low[v] = min(low[v], disc[u]);
    }

    if (parent == -1 && children > 1)
        ap[v] = true;
}

int main() {
    int V, E;
    cin >> V >> E;

    vector<vector<int>> adj(V);

    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> disc(V, 0), low(V, 0);
    vector<bool> ap(V, false);

    for (int i = 0; i < V; i++)
        if (!disc[i])
            DFS(i, -1, adj, disc, low, ap);

    cout << "Articulation Points:\n";
    for (int i = 0; i < V; i++)
        if (ap[i]) cout << i << " ";
}
