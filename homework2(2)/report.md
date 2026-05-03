# 41343122
# 41343133
作業二(Graph)

## 解題說明

這次作業實作多種Graph相關演算法與資料結構，包括：

圖形表示法
- Adjacency Matrix

- Adjacency List

- Adjacency Multilist

圖形走訪

- Depth First Search（DFS）
- Breadth First Search（BFS）

圖形分析

- Connected Components
- Spanning Tree
- Biconnected Components

最佳化問題

- Kruskal’s Algorithm
- Prim’s Algorithm

最短路徑

- All Destination: Nonnegative Edge CostsEdge Costs（非負權重）
- All Destination: General WeightsWeights（含負權重）
- All-Pairs Shortest Paths（全點對）

排程問題

- AOV（Topological Sort)
- AOE（Critical Path）

### 解題策略
# Graph 作業解題策略

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

Dijkstra（非負最短路徑）  
每次選擇目前距離最小節點進行擴展並更新鄰居距離。  
使用 greedy + priority queue，但不能處理負權重。

---

Bellman-Ford（含負權）  
對所有邊重複進行 V-1 次鬆弛操作更新距離。  
可處理負權並能偵測負權環。

---

Floyd-Warshall（全點對最短路徑）  
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

| 測試案例 | 輸入內容 | 預期輸出 |
|-----------|-----------|-----------|
| 測試一 | A = 2X² + 3X + 1<br>B = X² + 2X + 3<br>x = 2 | A+B = 3X²+5X+4<br>A×B = 2X⁴+7X³+11X²+9X+3<br>A(2)=15<br>B(2)=11 |
| 測試二 | A = 5X³ - 2X + 1<br>B = -3X² + 4X - 2<br>x = -1 | A+B = 5X³-3X²+2X-1<br>A×B = -15X⁵+20X⁴-7X³+14X²-8X+2<br>A(-1)=-2<br>B(-1)=-9 |
| 測試三 | A = X⁴ + 2X² + 3<br>B = 3X + 1<br>x = 3 | A+B = X⁴+2X²+3X+4<br>A×B = 3X⁵+X⁴+6X³+2X²+9X+3<br>A(3)=96<br>B(3)=10 |
| 測試四 | A = 0 <br>B = 4X² + 2X + 1<br>x = 5 | A+B = 4X²+2X+1<br>A×B = 0<br>A(5)=0<br>B(5)=111 |
| 測試五 | A = X⁵ + X⁴ + X³ + X² + X + 1<br>B = X + 1<br>x = 2 | A+B = X⁵+X⁴+X³+X²+2X+2<br>A×B = X⁶+2X⁵+2X⁴+2X³+2X²+2X+1<br>A(2)=63<br>B(2)=3 |

---

### 實際執行結果
(測試一)
```shell
$ g++ main.cpp --std=c++21 -o main.exe
$ ./main.exe
3
2 2
3 1
1 0
3
1 2
2 1
3 0
2
3X^2+5X+4
2X^4+7X^3+11X^2+9X+3
15
11

(測試二)
$ ./main.exe
$ g++ main.cpp --std=c++21 -o main.exe
3
5 3
-2 1
1 0
3
-3 2
4 1
-2 0
-1
5X^3-3X^2+2X-1
-15X^5+20X^4-7X^3+14X^2-8X+2
-2
-9
```


### 結論

所有測試案例輸出結果均與理論計算一致，加法、乘法與代入運算在各種多項式下皆能正確執行，
程式能處理常數項、負係數、不同次數與零多項式等特殊情況，經多組驗證後，程式穩定、無中斷錯誤，運算邏輯正確。

## 申論及開發報告

### 選擇遞迴的原因
在經過上機實習學會如何寫出`Add()`函式後，採用動態陣列來儲存多項式各項，能根據實際輸入項數自動擴充容量，避免固定陣列的空間浪費。
初版程式在 Mult() 執行時出現中斷點錯誤，原因是動態記憶體擴充後指標失效。後來改良 `newTerm()`，在新增項目前檢查是否已有相同指數項並即時合併，成功解決中斷點問題。
程式穩定執行後，輸出結果完全正確。透過這次作業了解了多項式的物件導向封裝概念，以及在 C++ 中使用動態記憶體時需注意的擴充與合併細節。
除錯過程讓我更清楚記憶體操作的重要性，也體驗到如何讓程式更穩定可靠。

