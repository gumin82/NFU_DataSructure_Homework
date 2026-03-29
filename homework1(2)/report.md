# 41343133
作業1
## problem1 MinHeap
## 解題說明
作業要求實作一個MinHeap，包含Push、Top、Pop、IsEmpty
MinHeap 每個節點的值都小於等於其子節點根節點為整體最小值

### 解題策略
作業採用「陣列實作的二元堆（Binary Heap）」：
1. 使用 1-based indexing
2. 父節點與子節點關係：
   - parent = i / 2
   - left child = 2i
   - right child = 2i + 1
3. Push：
   - 將新元素放到最後
   - 透過「向上調整（heapify up）」維持堆性質
4. Pop：
   - 將最後一個元素移到根
   - 透過「向下調整」維持堆性質
## 2. 程式實作

```cpp
#include <iostream>
using namespace std;

template <class T>
class MinPQ {
public:
    virtual ~MinPQ() {}
    virtual bool IsEmpty() const = 0;
    virtual const T& Top() const = 0;
    virtual void Push(const T&) = 0;
    virtual void Pop() = 0;
};

template <class T>
class MinHeap : public MinPQ<T> {
private:
    T* heap;
    int heapSize;
    int capacity;

    void resize() {
        capacity *= 2;
        T* newHeap = new T[capacity + 1];
        for (int i = 1; i <= heapSize; i++)
            newHeap[i] = heap[i];
        delete[] heap;
        heap = newHeap;
    }

public:
    MinHeap(int cap = 10) {
        capacity = cap;
        heapSize = 0;
        heap = new T[capacity + 1];
    }

    ~MinHeap() {
        delete[] heap;
    }

    bool IsEmpty() const override {
        return heapSize == 0;
    }

    const T& Top() const override {
        if (IsEmpty()) throw "Heap is empty";
        return heap[1];
    }

    void Push(const T& e) override {
        if (heapSize == capacity)
            resize();

        int current = ++heapSize;

        while (current != 1 && heap[current / 2] > e) {
            heap[current] = heap[current / 2];
            current /= 2;
        }

        heap[current] = e;
    }

    void Pop() override {
        if (IsEmpty()) throw "Heap is empty";

        T last = heap[heapSize--];

        int current = 1;
        int child = 2;

        while (child <= heapSize) {
            if (child < heapSize && heap[child] > heap[child + 1])
                child++;
            if (last <= heap[child]) break;
            heap[current] = heap[child];
            current = child;
            child *= 2;
        }
        heap[current] = last;
    }

    void Print() const {
        for (int i = 1; i <= heapSize; i++)
            cout << heap[i] << " ";
        cout << endl;
    }
};

int main() {
    MinHeap<int> h;
    h.Push(1);
    h.Push(2);
    h.Push(4);
    h.Push(3);

    cout << "Top: " << h.Top() << endl;

    h.Pop();

    cout << "Pop: ";
    h.Print();

    return 0;
}
```
## 效能分析
Push時間複雜度：
𝑂
(
log
⁡
𝑛
)
O(logn)
Pop時間複雜度：
𝑂
(
log
⁡
𝑛
)
O(logn)
Top時間複雜度：
𝑂
(
1
)
O(1)
空間複雜度：
𝑂
(
𝑛
)
O(n)
### 測試與驗證
### 編譯與執行指令
```shell
$ g++ main.cpp --std=c++21 -o main.exe
$ .\main.exe
執行結果
Top: 1
Pop: 2 3 4
```
### 結論
透過本作業，我學會：

Min Heap 的結構與操作
如何用陣列實作二元堆
Heapify up / down 的原理
資料結構在實務上的應用

## 申論及開發報告

使用「Min Heap」作為資料結構：
效率高
插入與刪除皆為 
𝑂
(
log
⁡
𝑛
)
O(logn)
查找最小值為 
𝑂
(
1
)
O(1)
適合優先權佇列（Priority Queue）
Min Heap 可以快速取得最小元素
適合用於：
排程系統
最短路徑演算法（Dijkstra）
資料排序
陣列實作優點
空間連續
存取速度快
不需要指標操作（比 linked list 更簡單）
可擴充性
使用 resize() 動態擴充容量
避免固定大小限制

