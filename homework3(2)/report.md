
# 41343122
# 41343133

## 解題說明

本作業旨在實作多種經典排序演算法，並透過 Benchmark 測試分析各演算法在不同資料規模與不同測試情境下的執行效率與記憶體使用情形。

測試資料規模為 n = 500、1000、2000、3000、4000、5000，並分別針對 Best Case、Average Case 與 Worst Case 進行實驗。

本次作業實作以下五種排序演算法：
### Insertion Sort
其核心概念為維持一個已排序區間，並將未排序區間中的元素依序插入到正確位置。
當資料量較小或資料本身接近排序完成時，Insertion Sort 具有不錯的執行效率，但在資料量較大時，由於需要頻繁移動元素，效率會明顯下降。
---
### Quick Sort
本作業採用 Median-of-Three 方法選擇 Pivot，即從左端、中間及右端三個元素中選取中位數作為 Pivot

其主要流程如下：

- 選擇一個 Pivot（基準值）
- 將資料分割成小於 Pivot 與大於 Pivot 的兩部分
- 分別遞迴排序左右子區間
### 解題策略
### Graph 作業解題策略

圖的表示法  
鄰接矩陣：用二維陣列表示點與點關係，適合快速查詢但空間為 O(V^2)，適合稠密圖。  
鄰接串列：每個點存鄰居列表，空間 O(V+E)，適合遍歷與稀疏圖（本作業主要使用）。  
鄰接多重串列：邊只存一次並連接兩端點，適合需要操作邊的進階情況。

---

DFS（深度優先搜尋）  
從起點一路深入未訪問節點，走到底再回溯，用於連通分量、生成樹與割點分析。  
透過遞迴或 stack 實作，適合需要完整探索路徑的問題。

---

BFS（廣度優先搜尋）  
使用 queue 逐層擴展節點，先處理距離近的節點。  
在無權圖中可求最短路徑，適合層級式搜尋問題。

---

Connected Components（連通分量）  
對每個未訪問節點執行 DFS/BFS，將可達節點分為同一群。  
重複直到所有節點訪問完成，即可得到所有連通區塊。

---

Spanning Tree（生成樹）  
在 DFS/BFS 過程中記錄第一次訪問所使用的邊，形成無環且涵蓋所有節點的樹。  
邊數固定為 V-1。

---

Biconnected Components（雙連通分量）  
使用 DFS 搭配 dfn 與 low 值判斷節點是否為割點。  
若 low[v] >= dfn[u]，表示 u 為割點，移除會造成圖分裂。

---

Kruskal（最小生成樹）  
將邊依權重排序，依序加入最小邊並用 Union-Find 避免成環。  
適合稀疏圖，重點在「選邊而不是選點」。

---

Prim（最小生成樹）  
從任一節點開始，每次選擇與目前樹相連的最小邊擴展。  
使用 priority queue 維護候選邊，適合稠密圖。

---

All Destination: Nonnegative Edge CostsEdge Costs（非負最短路徑）  
每次選擇目前距離最小節點進行擴展並更新鄰居距離。  
使用 greedy + priority queue，但不能處理負權重。

---

All Destination: General WeightsWeights（含負權）  
對所有邊重複進行 V-1 次鬆弛操作更新距離。  
可處理負權並能偵測負權環。

---

All-Pairs Shortest Paths（全點對最短路徑）  
透過三層迴圈嘗試每個中繼點是否能縮短任意兩點距離。  
核心為動態規劃，時間複雜度 O(V^3)。

---

AOV（拓撲排序）  
每次選擇入度為 0 的節點輸出並移除其影響。  
若無法完成排序代表圖中存在環。

---

AOE（關鍵路徑）  
計算每個節點最早與最晚時間，找出不影響總工期的關鍵邊。  
關鍵路徑決定專案最短完成時間。

## 程式實作
Adjacency Matrix 程式碼：

```cpp
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
```

Adjacency lists 程式碼：

```cpp
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
```

Adjacency Multilist 程式碼：
```cpp
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
```

Depth First Search（DFS）程式碼:
```cpp
#include <iostream>
#include <vector>
using namespace std;

void DFS(int v, vector<vector<int>>& adj, vector<bool>& visited){
    visited[v]=true;
    cout<<v<<" ";

    for(int u: adj[v])
        if(!visited[u])
            DFS(u,adj,visited);
}

int main(){
    int V,E;
    cin>>V>>E;

    vector<vector<int>> adj(V);

    for(int i=0;i<E;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<bool> visited(V,false);

    cout<<"DFS: ";
    DFS(0,adj,visited);
}
```

Breadth First Search（BFS）程式碼:
```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main(){
    int V,E;
    cin>>V>>E;

    vector<vector<int>> adj(V);

    for(int i=0;i<E;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<bool> visited(V,false);
    queue<int> q;

    q.push(0);
    visited[0]=true;

    cout<<"BFS: ";

    while(!q.empty()){
        int v=q.front(); q.pop();
        cout<<v<<" ";

        for(int u: adj[v]){
            if(!visited[u]){
                visited[u]=true;
                q.push(u);
            }
        }
    }
}
```

Connected Components 程式碼:
```cpp
#include <iostream>
#include <vector>
using namespace std;

void DFS(int v, vector<vector<int>>& adj, vector<bool>& visited){
    visited[v]=true;
    cout<<v<<" ";

    for(int u: adj[v])
        if(!visited[u])
            DFS(u,adj,visited);
}

int main(){
    int V,E;
    cin>>V>>E;

    vector<vector<int>> adj(V);

    for(int i=0;i<E;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<bool> visited(V,false);
    int count=0;

    for(int i=0;i<V;i++){
        if(!visited[i]){
            cout<<"Component "<<++count<<": ";
            DFS(i,adj,visited);
            cout<<endl;
        }
    }
}
```

Spanning Tree 程式碼:
```cpp
#include <iostream>
#include <vector>
using namespace std;

void DFS(int v, vector<vector<int>>& adj, vector<bool>& visited){
    visited[v]=true;

    for(int u: adj[v]){
        if(!visited[u]){
            cout<<v<<" - "<<u<<endl;
            DFS(u,adj,visited);
        }
    }
}

int main(){
    int V,E;
    cin>>V>>E;

    vector<vector<int>> adj(V);

    for(int i=0;i<E;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<bool> visited(V,false);

    cout<<"Spanning Tree edges:\n";
    DFS(0,adj,visited);
}
```

Biconnected Components 程式碼:
```cpp
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
```

Kruskal’s Algorithm 程式碼:
```cpp
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
```

Prim’s Algorithm 程式碼:
```cpp
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
```

Nonnegative Edge CostsEdge Costs 程式碼:
```cpp
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
```

General WeightsWeights 程式碼:
```cpp
#include <iostream>
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
```

All-Pairs Shortest Paths 程式碼:
```cpp
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
```

AOV 程式碼:
```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main(){
    int V,E;
    cin>>V>>E;

    vector<vector<int>> adj(V);
    vector<int> indegree(V,0);

    for(int i=0;i<E;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        indegree[v]++;
    }

    queue<int> q;
    for(int i=0;i<V;i++)
        if(indegree[i]==0) q.push(i);

    cout<<"Topological Order: ";

    while(!q.empty()){
        int u=q.front(); q.pop();
        cout<<u<<" ";

        for(int v: adj[u]){
            if(--indegree[v]==0)
                q.push(v);
        }
    }
}
```

AOE 程式碼:
```cpp
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
```

## 效能分析

| 演算法                    | 時間複雜度      | 空間複雜度    |
| ---------------------- | ---------- | -------- |
| Adjacency Matrix       | O(1)   | O(V²)    |
| Adjacency List         | O(V + E)   | O(V + E) |
| Adjacency Multilist    | O(V + E)   | O(V + E) |
| DFS                    | O(V + E)   | O(V)     |
| BFS                    | O(V + E)   | O(V)     |
| Connected Components   | O(V + E)   | O(V)     |
| Spanning Tree          | O(V + E)   | O(V)     |
| Biconnected Components | O(V + E)   | O(V)     |
| Kruskal’s Algorithm    | O(E log E) | O(V)     |
| Prim’s Algorithm       | O(E log V) | O(V)     |
|Nonnegative Edge CostsEdge Costs | O(E log V) | O(V)     |
| General WeightsWeights   | O(VE)      | O(V)     |
| All-Pairs Shortest Paths   | O(V³)      | O(V²)    |
| AOV  | O(V + E)   | O(V)     |
| AOE     | O(V + E)   | O(V)     |


## 測試與驗證

### 測試案例

| 測試項目                               | 輸入內容                                                               | 預期輸出                                                                                                             |
| ---------------------------------- | ------------------------------------------------------------------ | ---------------------------------------------------------------------------------------------------------------- |
| **Adjacency Matrix（含權重 / 無權重）**    | 4 3<br>0 1 5<br>1 2 3<br>2 3 2                                     | 無權重矩陣:<br>0 1 0 0<br>1 0 1 0<br>0 1 0 1<br>0 0 1 0<br><br>有權重矩陣:<br>0 5 0 0<br>5 0 3 0<br>0 3 0 2<br>0 0 2 0     |
| **Adjacency List（含權重 / 無權重）**      | 4 3<br>0 1 5<br>1 2 3<br>2 3 2                                     | 無權重:<br>0: 1<br>1: 0 2<br>2: 1 3<br>3: 2<br><br>有權重:<br>0: (1,5)<br>1: (0,5) (2,3)<br>2: (1,3) (3,2)<br>3: (2,2) |
| **Adjacency Multilist（含權重 / 無權重）** | 4 3<br>0 1 5<br>1 2 3<br>2 3 2                                     | 無權重:<br>0: 1<br>1: 0 2<br>2: 1 3<br>3: 2<br><br>有權重:<br>0: (1,5)<br>1: (0,5) (2,3)<br>2: (1,3) (3,2)<br>3: (2,2) |
| DFS / BFS / Spanning Tree          | 5 4<br>0 1<br>0 2<br>1 3<br>2 4                                    | DFS: 0 1 3 2 4<br>BFS: 0 1 2 3 4<br>Spanning Tree:<br>0-1, 1-3, 0-2, 2-4                                         |
| Connected Components               | 6 3<br>0 1<br>1 2<br>3 4                                           | Component 1: 0 1 2<br>Component 2: 3 4<br>Component 3: 5                                                         |
| Kruskal / Prim                | 4 5<br>0 1 5<br>0 2 2<br>1 2 1<br>1 3 3<br>2 3 4                   | MST edges:<br>1-2(1), 0-2(2), 1-3(3)<br>Total cost: 6                                                            |
| Nonnegative Edge CostsEdge Costs / General WeightsWeights  | 4 5<br>0 1 5<br>0 2 2<br>1 2 1<br>1 3 3<br>2 3 4<br>start=0   | dist[0]=0<br>dist[1]=5<br>dist[2]=2<br>dist[3]=6                                                                 |
| All-Pairs Shortest Paths                     | 4<br>0 5 2 999<br>999 0 1 3<br>999 999 0 4<br>999 999 999 0        | 0 5 2 6<br>∞ 0 1 3<br>∞ ∞ 0 4<br>∞ ∞ ∞ 0                                                                         |
| AOV                   | 6 6<br>0 1<br>0 2<br>1 3<br>2 3<br>3 4<br>4 5                      | Topological Order:<br>0 1 2 3 4 5                                                                                |
| AOE                 | 6 7<br>0 1 3<br>0 2 2<br>1 3 2<br>2 3 1<br>3 4 4<br>4 5 2<br>2 5 6 | Earliest time:<br>v0:0 v1:3 v2:2 v3:5 v4:9 v5:11                                                                 |


---


### 結論

本次作業透過實作多種 Graph 相關資料結構與演算法，使我能夠理解圖在不同情境下的表示方式與應用差異。

從鄰接矩陣、鄰接串列到鄰接多重串列，可以比較不同結構在空間與操作效率上的取捨。

在演算法部分，透過 DFS 與 BFS 掌握圖的遍歷方式，並延伸至連通分量、生成樹與雙連通分量等結構分析問題。

實作最小生成樹與最短路徑演算法，理解 Kruskal、Prim 及 All Destination: Nonnegative Edge CostsEdge Costs、All Destination: General WeightsWeights、All-Pairs Shortest Paths 等方法的適用條件與限制。

最後在 AOV 與 AOE 排程問題中，體會拓撲排序與關鍵路徑在實務專案中的應用。

本作業整體加強了我對圖論架構與問題拆解能力的理解。

## 申論及開發報告

這次作業主要是圍繞 Graph 的各種基礎與進階應用進行實作。

在設計資料結構時，其實對鄰接矩陣與鄰接串列的差異沒有很深的概念，只知道一個是用**二維陣列**，一個是用**vector**。

實作之後才發現，兩者最大的差別其實是在「資料規模」與「使用情境」，例如**鄰接矩陣雖然查詢很快**，但**在節點數變大時會非常浪費記憶體**，而鄰接串列則更適合實際大部分的圖問題。

在 DFS 與 BFS 的部分，一開始容易搞混兩者的使用方式，尤其是在 recursive DFS 和 queue BFS 的差別。

不過透過實際寫程式之後，可以明顯感受到 **DFS 比較像是深入探索**，而 **BFS 則是一層一層擴展**

兩者在解不同問題時有明顯用途差異，例如 **BFS 比較適合找最短路徑**，而 **DFS 則常用在結構分析**

在進階部分如 MST、最短路徑與 AOV/AOE，我才比較明確理解**同一個問題其實可以有不同解法**

例如 Kruskal 與 Prim 雖然都在找**最小生成樹**，但一個是從**邊**的角度思考，一個是從**點**的角度擴展。

而最短路徑部分也讓我理解不同演算法的限制，例如 **All Destination: Nonnegative Edge CostsEdge Costs 不能處理負權重**，而 **All Destination: General WeightsWeights 則可以，但效率較低**。

整體來說，這次作業不只是單純把演算法寫出來，而是讓我更清楚理解每個 Graph 問題背後的思考方式，以及如何根據條件選擇適合的解法。

在實作過程中也讓我對 C++ 的資料結構操作更加熟悉，尤其是 vector、priority queue 與 recursive DFS 的使用方式。
