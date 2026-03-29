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
##  程式實作

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
 $O(logn)$ 
 
Pop時間複雜度：
 $O(logn)$
 
Top時間複雜度：
 $O(1)$
 
空間複雜度：
 $O(n)$
 
## 測試與驗證
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
## Problem 2 Binary Search Tree（BST)
## 解題說明

Binary Search Tree（BST）是一種特殊的二元樹，其滿足以下性質：

左子樹的所有節點值 小於根節點
右子樹的所有節點值 大於根節點
每個子樹本身也是一棵 BST

本題要求實作 BST，並完成Insert、Delete、Height、Inorder Traversal
測量隨機資料下的樹高度並分析
### 解題策略
採用 遞迴方式實作 BST
插入時：
小於 → 左子樹
大於 → 右子樹
刪除節點分為三種情況：
無子節點
單一子節點
兩個子節點（用右子樹最小值替代）
使用中序走訪驗證 BST 是否正確
透過 rand() 測試不同 n 值的高度變化
## 程式實作
```cpp
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

template <class T>
struct Node {
    T data;
    Node* left;
    Node* right;

    Node(T x) : data(x), left(nullptr), right(nullptr) {}
};

template <class T>
class BST {
private:
    Node<T>* root;

    Node<T>* insert(Node<T>* node, T x) {
        if (!node) return new Node<T>(x);

        if (x < node->data)
            node->left = insert(node->left, x);
        else
            node->right = insert(node->right, x);

        return node;
    }

    int height(Node<T>* node) {
        if (!node) return 0;
        return 1 + max(height(node->left), height(node->right));
    }

    Node<T>* remove(Node<T>* node, T key) {
        if (!node) return nullptr;

        if (key < node->data)
            node->left = remove(node->left, key);
        else if (key > node->data)
            node->right = remove(node->right, key);
        else {
            if (!node->left) return node->right;
            if (!node->right) return node->left;
            Node<T>* minNode = node->right;
            while (minNode->left)
                minNode = minNode->left;

            node->data = minNode->data;
            node->right = remove(node->right, minNode->data);
        }

        return node;
    }

    void inorder(Node<T>* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

public:
    BST() : root(nullptr) {}

    void insert(T x) {
        root = insert(root, x);
    }

    void remove(T key) {
        root = remove(root, key);
    }

    int getHeight() {
        return height(root);
    }

    void print() {
        inorder(root);
        cout << endl;
    }
};
int main() {
    srand(time(0));

    cout << "A" << endl;

    int testCases[] = {100, 500, 1000, 2000, 3000, 5000, 10000};

    for (int i = 0; i < 7; i++) {
        int n = testCases[i];
        BST<int> tree;

        for (int j = 0; j < n; j++) {
            tree.insert(rand());
        }

        double h = tree.getHeight();
        double ratio = h / log2(n);

        cout << "n=" << n
             << ", height=" << h
             << ", h/log2(n)=" << ratio << endl;
    }

    cout << "B" << endl;

    BST<int> tree;

    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    cout << "Before: ";
    tree.print();

    tree.remove(30);

    cout << "After: ";
    tree.print();

    return 0;
}
```
## 效能分析
🔹 時間複雜度
操作	複雜度
插入	$O(h)$
刪除	$O(h)$
查找	$O(h)$

其中：

$h$ = 樹高度
平均情況：$h ≈ \log n$
最壞情況：$h = n$（退化成鏈結串列）
🔹 高度分析

透過測試結果：

ℎ
log
⁡
2
(
𝑛
)
log
2
	​

(n)
h
	​

若接近 1 → 表示樹接近平衡
若很大 → 表示樹退化
## 測試與驗證
### 測試案例
多組隨機資料插入（n = 100 ~ 10000）
計算樹高度
計算 $h / \log_2(n)$
測試刪除節點功能
測試結果
測試	說明
n = 100 ~ 10000	成功建立 BST
高度	隨 n 增加而增加
刪除	可正確刪除節點
結構	中序走訪仍保持排序
### 編譯與執行指令

```shell
$ g++ -std=c++17 -o bst bst.cpp
$ ./bst
A
n=100, height=14, h/log2(n)=2.10721
n=500, height=17, h/log2(n)=1.8961
n=1000, height=23, h/log2(n)=2.3079
n=2000, height=25, h/log2(n)=2.27982
n=3000, height=25, h/log2(n)=2.16436
n=5000, height=27, h/log2(n)=2.19732
n=10000, height=37, h/log2(n)=2.78453
B
Before: 20 30 40 50 60 70 80
After: 20 40 50 60 70 80
```
## 結論

本程式成功實作 BST 的基本功能：

插入（Insert）
刪除（Remove）
中序走訪（Inorder）
高度計算（Height）

透過隨機資料測試，可以觀察到：

BST 的高度會隨資料分布變化
若資料隨機，BST 接近平衡
若資料有序，可能退化成鏈結串列

因此，BST 在實務中常搭配：

AVL Tree
Red-Black Tree

來維持平衡性。

## 申論及開發報告

在本次實作中，我使用遞迴方式設計 BST，讓程式結構清晰且符合數學定義。

在刪除節點時，特別處理三種情況，其中「兩個子節點」需找到右子樹的最小值作為替代節點，這是 BST 中較為重要且較難實作的部分。

在效能分析中，我透過隨機資料建立多棵 BST，並計算其高度與 $\log_2(n)$ 的比例，觀察其是否接近理論值。

透過本次作業，我更加理解：

BST 的遞迴特性
樹高度對效能的影響
資料分布對資料結構的影響
