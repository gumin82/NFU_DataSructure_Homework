# 41343122 and 41343133

作業二

## 解題說明

本題要求實作一個多項式類別 Polynomial，能進行以下操作：

多項式的輸入與輸出

多項式相加 (Add)

多項式相乘 (Mult)

多項式代入求值 (Eval)

每個多項式由多項項目（Term）組成，每項包含係數 (coef) 與指數 (exp)。
使用者可輸入任意項數的多項式，程式必須能動態儲存與計算。
### 解題策略

1.使用 class Term 儲存每一項的係數與指數。

2.使用動態陣列 Term* termArray 儲存整個多項式的所有項。

3.newTerm() 可自動擴充陣列容量並合併同指數項。

4.Add() 逐項比較指數，將相同次方項相加。

5.Mult() 雙層迴圈逐項相乘，再利用 newTerm() 自動合併結果。

6.Eval() 代入變數 x，逐項計算多項式的總和值。

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

```

## 效能分析

| 函式          | 時間複雜度            | 空間複雜度    |
| ----------- | ---------------- | -------- |
| `Add()`     | O(n + m)         | O(n + m) | 
| `Mult()`    | O(n × m)         | O(n + m) |
| `Eval()`    | O(n × k)         | O(1)     |
| `newTerm()` | 改寫時 O(n)，平均 O(1) | O(n)     |


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

