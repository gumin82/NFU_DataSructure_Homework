# 41343133

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

以下為主要程式碼：

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

class Polynomial;

class Term {
    friend Polynomial;
    friend ostream& operator<<(ostream& output, const Polynomial& Poly);
private:
    int exp;
    float coef;
};

class Polynomial {
private:
    Term* termArray;
    int capacity;
    int terms;
public:
    Polynomial() : capacity(2), terms(0) {
        termArray = new Term[capacity];
    }
    ~Polynomial() { delete[] termArray; }
    Polynomial Add(const Polynomial& b) const;
    Polynomial Mult(const Polynomial& b) const;
    float Eval(float x) const;
    void newTerm(const float newcoef, const int newexp);
    friend istream& operator>>(istream& input, Polynomial& Poly);
    friend ostream& operator<<(ostream& output, const Polynomial& Poly);
};

istream& operator>>(istream& is, Polynomial& poly) {
    float coef;
    int exp, n;
    is >> n;
    while (n--) {
        is >> coef >> exp;
        poly.newTerm(coef, exp);
    }
    return is;
}

ostream& operator<<(ostream& os, const Polynomial& poly) {
    for (int i = 0; i < poly.terms; ++i) {
        if (i > 0 && poly.termArray[i].coef > 0) os << "+";
        os << poly.termArray[i].coef;
        if (poly.termArray[i].exp > 0) {
            os << "X";
            if (poly.termArray[i].exp > 1) os << "^" << poly.termArray[i].exp;
        }
    }
    return os;
}

void Polynomial::newTerm(const float theCoef, const int theExp) {
    if (theCoef == 0) return;
    if (terms == capacity) {
        capacity *= 2;
        Term* temp = new Term[capacity];
        copy(termArray, termArray + terms, temp);
        delete[] termArray;
        termArray = temp;
    }
    for (int i = 0; i < terms; i++) {
        if (termArray[i].exp == theExp) {
            termArray[i].coef += theCoef;
            return;
        }
    }
    termArray[terms].coef = theCoef;
    termArray[terms].exp = theExp;
    terms++;
}

Polynomial Polynomial::Add(const Polynomial& b) const {
    Polynomial c;
    int aPos = 0, bPos = 0;
    while (aPos < terms && bPos < b.terms) {
        if (termArray[aPos].exp == b.termArray[bPos].exp) {
            float t = termArray[aPos].coef + b.termArray[bPos].coef;
            if (t) c.newTerm(t, termArray[aPos].exp);
            aPos++; bPos++;
        } else if (termArray[aPos].exp > b.termArray[bPos].exp) {
            c.newTerm(termArray[aPos].coef, termArray[aPos].exp);
            aPos++;
        } else {
            c.newTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
            bPos++;
        }
    }
    for (; aPos < terms; aPos++)
        c.newTerm(termArray[aPos].coef, termArray[aPos].exp);
    for (; bPos < b.terms; bPos++)
        c.newTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
    return c;
}

Polynomial Polynomial::Mult(const Polynomial& b) const {
    Polynomial c;
    for (int i = 0; i < terms; i++) {
        for (int j = 0; j < b.terms; j++) {
            float newCoef = termArray[i].coef * b.termArray[j].coef;
            int newExp = termArray[i].exp + b.termArray[j].exp;
            c.newTerm(newCoef, newExp);
        }
    }
    return c;
}

float Polynomial::Eval(float x) const {
    float sum = 0;
    for (int i = 0; i < terms; i++) {
        float termValue = termArray[i].coef;
        for (int j = 0; j < termArray[i].exp; j++)
            termValue *= x;
        sum += termValue;
    }
    return sum;
}

int main() {
    Polynomial A, B;
    cin >> A;
    cin >> B;
    Polynomial C = A.Add(B);
    Polynomial D = A.Mult(B);
    float x;
    cin >> x;
    cout << C << endl;
    cout << D << endl;
    cout << A.Eval(x) << endl;
    cout << B.Eval(x) << endl;
    return 0;
}

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
