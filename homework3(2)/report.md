
# 41343122
# 41343133

## 解題說明

本作業旨在實作多種經典排序演算法，並透過 Benchmark 測試分析各演算法在不同資料規模與不同測試情境下的執行效率與記憶體使用情形。

測試資料規模為 n = 500、1000、2000、3000、4000、5000，並分別針對 Best Case、Average Case 與 Worst Case 進行實驗。

**本次作業實作以下五種排序演算法：**

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

---
### Merge Sort
本作業採用 Iterative Merge Sort（迭代式 Merge Sort），利用 Bottom-Up 的方式逐步合併區間，避免遞迴呼叫所產生的額外負擔。

其作法為：

- 將資料切分成較小區間
- 個別排序
- 將兩個已排序區間合併

Merge Sort 在 Best Case、Average Case 與 Worst Case 下皆能維持穩定的時間複雜度。

---
### Heap Sort
Heap Sort（堆積排序）利用 Heap（堆積）資料結構完成排序。本作業使用 Max Heap

其流程如下：

- 建立 Max Heap
- 將根節點（最大值）與最後一個元素交換
- 重新調整 Heap
- 重複執行直到排序完成

Heap Sort 不需要額外的大量記憶體，因此具有良好的空間效率。

---
### Composite Sort
Composite Sort（混合排序）結合多種排序演算法的優點，依據資料規模選擇最適合的排序方法。

本作業設計如下：

- n ≤ 32：使用 Insertion Sort
- 32 < n ≤ 1500：使用 Quick Sort
- n > 1500：使用 Merge Sort

透過此方式，希望能兼顧小型資料的低成本排序以及大型資料的高效率排序，達到較佳的整體效能。

---
### Benchmark 測試
測試內容包含：

- Best Case（最佳情況）
- Average Case（平均情況）
- Worst Case（最差情況）

並量測：

- 執行時間（Execution Time）
- 記憶體使用量（Memory Usage）

最後將實驗結果輸出為 CSV 檔案，作為後續圖表繪製與效能分析之依據。
## 解題策略

本作業建立 Benchmark 系統分析五種排序演算法：

- Insertion Sort
- Quick Sort (Median-of-Three)
- Merge Sort 
- Heap Sort
- Composite Sort

主要流程如下：

1. 產生 Best、Average、Worst Case 測試資料。
2. 使用 copyArray() 複製資料，避免排序修改原始測資。
3. 利用 chrono 計算排序執行時間。
4. 利用 Windows API 量測記憶體使用量。
5. 每次排序後使用 isSorted() 驗證結果正確性。
6. 測試 n = 500、1000、2000、3000、4000、5000。
7. 將結果輸出至 sorting_result.csv。
8. 統計每個資料規模下最快的排序演算法。

Composite Sort 採用混合策略：

- n ≤ 32：Insertion Sort
- 32 < n ≤ 1500：Quick Sort
- n > 1500：Merge Sort

希望透過不同排序法的優勢互補，提升整體效能。

實驗設計分為三種情境：

- Best Case
使用已排序資料作為輸入，觀察各演算法在理想情況下的執行效率。
- Average Case
使用隨機亂序資料，並對每組輸入重複執行多次（Multiple Trials），取平均執行時間與記憶體使用量，以降低單次測試誤差。
- Worst Case（實驗式搜尋）
對 Merge Sort、Heap Sort 與 Quick Sort 使用大量隨機產生的測資進行測試

透過多次隨機輸入執行，選取其中執行時間最長者作為 Worst Case，用以模擬實務上最不利的輸入情況。

## 程式實作
```cpp
//41343133
//41343122
#include <iostream>
using namespace std;

void insertionSort(int arr[], int n)
{
    for(int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;

        while(j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
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
