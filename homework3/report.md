# 41343133

作業三

## 解題說明
本作業目標為實作一個 多項式（Polynomial）類別，其內部資料結構需使用自行實作的鏈結串列（Linked List）。
多項式需支援以下功能：

多項式輸入與輸出

多項式加法、減法與乘法

代入數值進行多項式求值

使用 Available List 管理節點記憶體

作業需實作下列類別：
ChainNode、Chain、ChainIterator、AvailableList、Polynomial


### 解題策略

使用 ChainNode 作為基本節點單位，並以 Chain 組成單向鏈結串列來儲存多項式的每一項（Term）。
透過 ChainIterator 進行串列走訪，使多項式運算可使用 iterator 方式撰寫，提升程式可讀性。
為了減少動態記憶體配置的成本，額外實作 Available List，用來回收不再使用的節點，並於需要時重新取用，符合資料結構課程中對記憶體管理的設計理念。

## 程式實作


```cpp
#include <iostream>
#include <cmath>
using namespace std;

template <class T> class Chain;
template <class T> class ChainIterator;
template <class T> class AvailableList;

template <class T>
class ChainNode {
    friend class Chain<T>;
    friend class ChainIterator<T>;
    friend class AvailableList<T>;
private:
    T element;
    ChainNode<T>* next;
public:
    ChainNode() : next(nullptr) {}
    ChainNode(const T& e) : element(e), next(nullptr) {}
    ChainNode(const T& e, ChainNode<T>* n) : element(e), next(n) {}
};

template <class T>
class ChainIterator {
private:
    ChainNode<T>* current;
public:
    ChainIterator(ChainNode<T>* p = nullptr) : current(p) {}
    T& operator*() const { return current->element; }
    T* operator->() const { return &current->element; }
    ChainIterator& operator++() {
        current = current->next;
        return *this;
    }
    bool operator!=(const ChainIterator& rhs) const {
        return current != rhs.current;
    }
};

template <class T>
class Chain {
    friend class AvailableList<T>;
private:
    ChainNode<T>* head;
public:
    Chain() : head(nullptr) {}
    ~Chain() {
        while (head) {
            ChainNode<T>* tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    ChainIterator<T> begin() const { return ChainIterator<T>(head); }
    ChainIterator<T> end() const { return ChainIterator<T>(nullptr); }

    void insertFront(const T& e) {
        head = new ChainNode<T>(e, head);
    }

    ChainNode<T>* release() {
        ChainNode<T>* tmp = head;
        head = nullptr;
        return tmp;
    }
};

template <class T>
class AvailableList {
private:
    static ChainNode<T>* available;
public:
    static ChainNode<T>* getNode() {
        if (!available) return nullptr;
        ChainNode<T>* node = available;
        available = available->next;
        node->next = nullptr;
        return node;
    }

    static void getBack(ChainNode<T>* first) {
        if (!first) return;
        ChainNode<T>* p = first;
        while (p->next) p = p->next;
        p->next = available;
        available = first;
    }
};

template <class T>
ChainNode<T>* AvailableList<T>::available = nullptr;

struct Term {
    double coef;
    int exp;
    Term(double c = 0, int e = 0) : coef(c), exp(e) {}
};

class Polynomial {
    friend istream& operator>>(istream&, Polynomial&);
    friend ostream& operator<<(ostream&, const Polynomial&);
private:
    Chain<Term> terms;
public:
    void newTerm(double c, int e) {
        if (c == 0) return;

        for (auto it = terms.begin(); it != terms.end(); ++it) {
            if (it->exp == e) {
                it->coef += c;
                return;
            }
        }
        terms.insertFront(Term(c, e));
    }

    double Evaluate(double x) const {
        double sum = 0;
        for (auto it = terms.begin(); it != terms.end(); ++it)
            sum += it->coef * pow(x, it->exp);
        return sum;
    }

    Polynomial operator+(const Polynomial& b) const {
        Polynomial r;
        for (auto it = terms.begin(); it != terms.end(); ++it)
            r.newTerm(it->coef, it->exp);
        for (auto it = b.terms.begin(); it != b.terms.end(); ++it)
            r.newTerm(it->coef, it->exp);
        return r;
    }

    Polynomial operator-(const Polynomial& b) const {
        Polynomial r;
        for (auto it = terms.begin(); it != terms.end(); ++it)
            r.newTerm(it->coef, it->exp);
        for (auto it = b.terms.begin(); it != b.terms.end(); ++it)
            r.newTerm(-it->coef, it->exp);
        return r;
    }

    Polynomial operator*(const Polynomial& b) const {
        Polynomial r;
        for (auto it1 = terms.begin(); it1 != terms.end(); ++it1)
            for (auto it2 = b.terms.begin(); it2 != b.terms.end(); ++it2)
                r.newTerm(it1->coef * it2->coef,
                    it1->exp + it2->exp);
        return r;
    }
};

istream& operator>>(istream& is, Polynomial& p) {
    int n;
    is >> n;
    for (int i = 0; i < n; i++) {
        double c;
        int e;
        is >> c >> e;
        p.newTerm(c, e);
    }
    return is;
}

ostream& operator<<(ostream& os, const Polynomial& p) {
    bool first = true;
    for (auto it = p.terms.begin(); it != p.terms.end(); ++it) {
        if (!first && it->coef > 0) os << "+";
        os << it->coef << "x^" << it->exp;
        first = false;
    }
    return os;
}

int main() {
    Polynomial A, B;
    cout << "A:";
    cin >> A;
    cout << "B:";
    cin >> B;
    //cout << "A=" << A << endl;
    //cout << "B=" << B << endl;
    cout << "A+B=" << A + B << endl;
    cout << "A-B=" << A - B << endl;
    cout << "A*B=" << A * B << endl;
    cout << "A(2)=" << A.Evaluate(2) << endl;
    return 0;
}
```

## 效能分析

加法 / 減法

時間複雜度：$O(n + m)$

空間複雜度：$O(n + m)$

乘法

時間複雜度：$O(n \times m)$

空間複雜度：$O(n \times m)$

Available List
時間複雜度:$O(1)$
空間複雜度:$O(1)$
## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 $n$ | 預期輸出 | 實際輸出 |
|----------|--------------|----------|----------|
| 測試一   | $n = 0$      | 0        | 0        |
| 測試二   | $n = 1$      | 1        | 1        |
| 測試三   | $n = 3$      | 6        | 6        |
| 測試四   | $n = 5$      | 15       | 15       |
| 測試五   | $n = -1$     | 異常拋出 | 異常拋出 |

### 編譯與執行指令

```shell
$ g++ -std=c++17 -o sigma sigma.cpp
$ ./sigma
6
```

### 結論

1. 程式能正確計算 $n$ 到 $1$ 的連加總和。  
2. 在 $n < 0$ 的情況下，程式會成功拋出異常，符合設計預期。  
3. 測試案例涵蓋了多種邊界情況（$n = 0$、$n = 1$、$n > 1$、$n < 0$），驗證程式的正確性。

## 申論及開發報告

### 選擇遞迴的原因

在本程式中，使用遞迴來計算連加總和的主要原因如下：

1. **程式邏輯簡單直觀**  
   遞迴的寫法能夠清楚表達「將問題拆解為更小的子問題」的核心概念。  
   例如，計算 $\Sigma(n)$ 的過程可分解為：  

   $$
   \Sigma(n) = n + \Sigma(n-1)
   $$

   當 $n$ 等於 1 或 0 時，直接返回結果，結束遞迴。

2. **易於理解與實現**  
   遞迴的程式碼更接近數學公式的表示方式，特別適合新手學習遞迴的基本概念。  
   以本程式為例：  

   ```cpp
   int sigma(int n) {
       if (n < 0)
           throw "n < 0";
       else if (n <= 1)
           return n;
       return n + sigma(n - 1);
   }
   ```

3. **遞迴的語意清楚**  
   在程式中，每次遞迴呼叫都代表一個「子問題的解」，而最終遞迴的返回結果會逐層相加，完成整體問題的求解。  
   這種設計簡化了邏輯，不需要額外變數來維護中間狀態。

透過遞迴實作 Sigma 計算，程式邏輯簡單且易於理解，特別適合展示遞迴的核心思想。然而，遞迴會因堆疊深度受到限制，當 $n$ 值過大時，應考慮使用迭代版本來避免 Stack Overflow 問題。
