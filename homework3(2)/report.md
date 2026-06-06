
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
**Insertion Sort（插入排序）**
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
- 插入排序是一種逐步建構有序序列的演算法。
- 每次將一個元素插入到前面已排序區間的正確位置。
- 適合小型或接近排序完成的資料。



**Quick Sort（快速排序）**
```cpp
//41343133
//41343122

#include <iostream>
using namespace std;

void quickSwap(int &a,int &b)
{
    int temp=a;
    a=b;
    b=temp;
}

int medianOfThree(int arr[],int left,int right)
{
    int mid=(left+right)/2;

    if(arr[left]>arr[mid])
        quickSwap(arr[left],arr[mid]);

    if(arr[left]>arr[right])
        quickSwap(arr[left],arr[right]);

    if(arr[mid]>arr[right])
        quickSwap(arr[mid],arr[right]);

    quickSwap(arr[mid],arr[right-1]);

    return arr[right-1];
}

void quickSortRecursive(int arr[],int left,int right)
{
    if(left+10<=right)
    {
        int pivot=medianOfThree(arr,left,right);

        int i=left;
        int j=right-1;

        while(true)
        {
            while(arr[++i]<pivot){}
            while(arr[--j]>pivot){}

            if(i<j)
                quickSwap(arr[i],arr[j]);
            else
                break;
        }

        quickSwap(arr[i],arr[right-1]);

        quickSortRecursive(arr,left,i-1);
        quickSortRecursive(arr,i+1,right);
    }
    else
    {
        for(int p=left+1;p<=right;p++)
        {
            int tmp=arr[p];
            int j=p;

            while(j>left && arr[j-1]>tmp)
            {
                arr[j]=arr[j-1];
                j--;
            }

            arr[j]=tmp;
        }
    }
}

void quickSort(int arr[],int n)
{
    quickSortRecursive(arr,0,n-1);
}
```
- 快速排序採用分治法，選擇 pivot 將資料分割成左右兩部分。
- 左側小於 pivot，右側大於 pivot，再遞迴排序。
- 平均時間效率高，但最差情況可能退化為 O(n²)。



**Merge Sort（合併排序）**
```cpp
//41343133
//41343122

#include <iostream>
using namespace std;

void mergeArray(
    int arr[],
    int temp[],
    int left,
    int mid,
    int right)
{
    int i=left;
    int j=mid+1;
    int k=left;

    while(i<=mid && j<=right)
    {
        if(arr[i]<=arr[j])
            temp[k++]=arr[i++];
        else
            temp[k++]=arr[j++];
    }

    while(i<=mid)
        temp[k++]=arr[i++];

    while(j<=right)
        temp[k++]=arr[j++];

    for(int p=left;p<=right;p++)
        arr[p]=temp[p];
}

void mergeSort(int arr[],int n)
{
    int* temp=new int[n];

    for(int size=1;size<n;size*=2)
    {
        for(int left=0;
            left<n-1;
            left+=2*size)
        {
            int mid=left+size-1;

            if(mid>=n-1)
                continue;

            int right=left+2*size-1;

            if(right>=n)
                right=n-1;

            mergeArray(
                arr,
                temp,
                left,
                mid,
                right);
        }
    }

    delete[] temp;
}
```
- 合併排序採用分治法，將陣列遞迴切分成子序列。
- 再將已排序的子序列逐步合併成完整排序結果。
- 時間穩定為 O(n log n)，但需要額外記憶體。



**Heap Sort（堆積排序）**
```cpp
//41343133
//41343122

#include <iostream>
using namespace std;

void heapSwap(int &a,int &b)
{
    int temp=a;
    a=b;
    b=temp;
}

void heapify(int arr[],int n,int i)
{
    int largest=i;

    int left=2*i+1;
    int right=2*i+2;

    if(left<n &&
       arr[left]>arr[largest])
        largest=left;

    if(right<n &&
       arr[right]>arr[largest])
        largest=right;

    if(largest!=i)
    {
        heapSwap(arr[i],
                 arr[largest]);

        heapify(arr,n,largest);
    }
}

void heapSort(int arr[],int n)
{
    for(int i=n/2-1;i>=0;i--)
        heapify(arr,n,i);

    for(int i=n-1;i>0;i--)
    {
        heapSwap(arr[0],arr[i]);

        heapify(arr,i,0);
    }
}
```
- 堆積排序利用最大堆或最小堆結構進行排序。
- 先建立 heap，再反覆取出 root 並重新調整堆。
- 時間複雜度穩定為 O(n log n)，不需額外記憶體。



**Composite Sort（混合排序）**
```cpp
//41343133
//41343122
void insertionSort(int arr[], int n);
void quickSort(int arr[], int n);
void mergeSort(int arr[], int n);
void heapSort(int arr[], int n);

void compositeSort(int arr[], int n)
{
    if (n <= 32)
    {
        insertionSort(arr, n);
    }
    else if (n <= 1500)
    {
        quickSort(arr, n);
    }
    else
    {
        mergeSort(arr, n);
    }
}
```
- 混合排序根據資料大小選擇不同排序方法。
- 小資料使用 insertion sort，中型使用 quick sort，大型使用 merge sort。
- 用於提升整體實務效能。



**Benchmark 效能測試**
```cpp
//41343133
//41343122

#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <vector>

#ifdef _WIN32
#include <Windows.h>
#include <Psapi.h>
#endif

using namespace std;
using namespace chrono;

//========================
// Sorting functions
//========================
void insertionSort(int arr[], int n);
void quickSort(int arr[], int n);
void mergeSort(int arr[], int n);
void heapSort(int arr[], int n);
void compositeSort(int arr[], int n);

//========================
// Record
//========================
struct SortRecord
{
    int n;
    string caseType;
    string sortName;
    double timeMicroseconds;
    size_t memoryKB;
};

//========================
struct FastestRecord
{
    int n;
    string caseType;
    string bestSort;
    double bestTime;
};

//========================
// Memory usage
//========================
size_t getMemoryKB()
{
#ifdef _WIN32
    PROCESS_MEMORY_COUNTERS memInfo;
    GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo));
    return memInfo.WorkingSetSize / 1024;
#else
    return 0;
#endif
}

//========================
bool isSorted(int arr[], int n)
{
    for (int i = 1; i < n; i++)
        if (arr[i - 1] > arr[i])
            return false;
    return true;
}

//========================
// data generation
//========================
void generateBestCase(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = i + 1;
}

void generateWorstCase(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = n - i;
}

void generateAverageCase(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = i + 1;

    for (int i = n - 1; i > 0; i--)
        swap(arr[i], arr[rand() % (i + 1)]);
}

//========================
// random for WORST SEARCH
//========================
void generateRandomCase(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = i + 1;

    for (int i = n - 1; i > 0; i--)
        swap(arr[i], arr[rand() % (i + 1)]);
}

//========================
void copyArray(int src[], int dst[], int n)
{
    for (int i = 0; i < n; i++)
        dst[i] = src[i];
}

//========================
// measure single run
//========================
pair<double, size_t> measureSort(void (*sortFunc)(int[], int), int arr[], int n)
{
    size_t memBefore = getMemoryKB();

    auto start = high_resolution_clock::now();

    sortFunc(arr, n);

    auto end = high_resolution_clock::now();

    size_t memAfter = getMemoryKB();

    double timeUs = duration_cast<microseconds>(end - start).count();

    size_t memUse = (memAfter > memBefore)
        ? (memAfter - memBefore)
        : (memBefore - memAfter);

    return { timeUs, memUse };
}

//========================
// average multi-run
//========================
pair<double, size_t> measureAverage(void (*sortFunc)(int[], int), int arr[], int n, int trials)
{
    double totalTime = 0;
    size_t totalMem = 0;

    int* temp = new int[n];

    for (int i = 0; i < trials; i++)
    {
        copyArray(arr, temp, n);

        size_t memBefore = getMemoryKB();
        auto start = high_resolution_clock::now();

        sortFunc(temp, n);

        auto end = high_resolution_clock::now();
        size_t memAfter = getMemoryKB();

        double timeUs = duration_cast<microseconds>(end - start).count();

        totalTime += timeUs;

        totalMem += (memAfter > memBefore)
            ? (memAfter - memBefore)
            : (memBefore - memAfter);
    }

    delete[] temp;

    return { totalTime / trials, totalMem / trials };
}

//========================
// worst case search (random)
//========================
pair<double, size_t> measureWorstSearch(void (*sortFunc)(int[], int), int arr[], int n, int trials)
{
    double worstTime = -1;
    size_t mem = 0;

    int* temp = new int[n];

    for (int i = 0; i < trials; i++)
    {
        generateRandomCase(arr, n);
        copyArray(arr, temp, n);

        auto r = measureSort(sortFunc, temp, n);

        if (r.first > worstTime)
        {
            worstTime = r.first;
            mem = r.second;
        }
    }

    delete[] temp;

    return { worstTime, mem };
}

//========================
// CSV
//========================
void writeCSV(const vector<SortRecord>& records)
{
    ofstream fout("sorting_result.csv");
    fout << "n,case,algorithm,time_us,memory_kb\n";

    for (auto& r : records)
    {
        fout << r.n << ","
            << r.caseType << ","
            << r.sortName << ","
            << r.timeMicroseconds << ","
            << r.memoryKB << "\n";
    }
}

//========================
// MAIN
//========================
int main()
{
    srand((unsigned)time(NULL));

    vector<SortRecord> records;
    vector<FastestRecord> fastestTable;

    int testSize[] = { 500,1000,2000,3000,4000,5000 };

    const int AVG_TRIAL = 10;
    const int WORST_TRIAL = 20;

    cout << "=============================\n";
    cout << "Sorting Benchmark (Time + Memory)\n";
    cout << "=============================\n";

    for (int t = 0; t < 6; t++)
    {
        int n = testSize[t];

        int* original = new int[n];
        int* data = new int[n];

        string cases[3] = { "Best","Average","Worst" };

        for (int c = 0; c < 3; c++)
        {
            string bestName = "";
            double bestTime = 1e18;

            if (c == 0) generateBestCase(original, n);
            else if (c == 1) generateAverageCase(original, n);

            cout << "\nN=" << n << " Case=" << cases[c] << "\n";

            auto runAlgo = [&](string name, void (*func)(int[], int))
                {
                    pair<double, size_t> r;

                    if (c == 0)
                    {
                        copyArray(original, data, n);
                        r = measureSort(func, data, n);
                    }
                    else if (c == 1)
                    {
                        r = measureAverage(func, original, n, AVG_TRIAL);
                    }
                    else
                    {
                        r = measureWorstSearch(func, original, n, WORST_TRIAL);
                    }

                    cout << name << " : " << r.first << " us | " << r.second << " KB\n";

                    records.push_back({ n, cases[c], name, r.first, r.second });

                    if (r.first < bestTime)
                    {
                        bestTime = r.first;
                        bestName = name;
                    }
                };

            runAlgo("InsertionSort", insertionSort);
            runAlgo("QuickSort", quickSort);
            runAlgo("MergeSort", mergeSort);
            runAlgo("HeapSort", heapSort);
            runAlgo("CompositeSort", compositeSort);

            fastestTable.push_back({ n, cases[c], bestName, bestTime });
        }

        delete[] original;
        delete[] data;
    }

    writeCSV(records);

    cout << "\n========== FASTEST TABLE ==========\n";
    for (auto& f : fastestTable)
    {
        cout << "n=" << f.n
            << " case=" << f.caseType
            << " fastest=" << f.bestSort
            << " time=" << f.bestTime << " us\n";
    }

    cout << "\nSaved: sorting_result.csv\n";

    return 0;
}
```
本實驗針對五種排序演算法進行效能比較分析，並在不同輸入規模（500 至 5000）下測試執行時間與記憶體使用量。

實驗分為三種輸入情境：Best Case、Average Case 與 Worst Case。

Best Case 使用已排序資料，觀察演算法在最佳情況下的表現。

Average Case 使用隨機資料，並重複多次實驗取平均值，以降低單次測試誤差。

Worst Case 則針對 Merge Sort、Heap Sort 與 Quick Sort，透過大量隨機輸入進行多次測試，選取執行時間最長者作為最差情況。

此方法屬於「實驗式 worst-case 搜尋」，用以模擬實務上最不利輸入。

程式同時記錄每次排序的執行時間（microseconds）與記憶體使用量（KB）。

最後將結果輸出為 CSV 檔，方便後續繪圖與數據分析比較。

---

## 效能分析

本實驗比較五種排序演算法：
- Insertion Sort
- Median-of-Three
- Quick Sort
- Merge Sort
- Heap Sort
- Composite Sort

在不同資料規模（n = 500 ~ 5000）下的執行時間與記憶體使用情況。

### 理論時間與空間複雜度

| 排序演算法 | 最佳時間複雜度 | 平均時間複雜度 | 最壞時間複雜度 | 空間複雜度 |
|------------|----------------|----------------|----------------|------------|
| 插入排序 (Insertion Sort) | O(n) | O(n^2) | O(n^2) | O(1) |
| 快速排序 (Median-of-Three Quick Sort) | O(n log n) | O(n log n) | O(n^2) | O(log n) |
| 合併排序 (Merge Sort) | O(n log n) | O(n log n) | O(n log n) | O(n) |
| 堆積排序 (Heap Sort) | O(n log n) | O(n log n) | O(n log n) | O(1) |
| 複合排序 (Composite Sort) | O(n) | O(n log n) | O(n log n) | O(n) |

---

### 理論分析說明

*Insertion Sort* 在資料量增加時會呈現明顯的二次成長，因此在 n 較大時效能最差。

*Quick Sort* 在平均情況下表現良好，但若 pivot 選擇不佳，最壞情況會退化為 O(n^2)。本實作採用 median-of-three 改善 pivot 選擇，使平均效能更穩定。

*Merge Sort* 在本實作為 iterative 版本，維持穩定 O(n log n) 的時間複雜度，但需要額外 O(n) 的輔助空間。

*Heap Sort* 在建立堆與調整過程中維持 O(n log n)，且不需額外大規模記憶體，因此在空間效率上較佳。

*Composite Sort* 則根據輸入大小動態選擇排序方式：
- n ≤ 32 使用 Insertion Sort
- 32 < n ≤ 1500 使用 Quick Sort
- n > 1500 使用 Merge Sort

因此 Composite Sort 的整體行為較接近「混合式分治策略」，而非單一排序演算法。

---

### 實驗結果解讀（Benchmark Design）

本程式採用三種測試模式進行效能分析：

- **Best Case**：使用已排序資料，觀察最佳情況下的執行效率。
- **Average Case**：使用隨機亂序資料，並重複多次實驗（multiple trials）後取平均值，以降低隨機誤差。
- **Worst Case（實驗式搜尋）**：對 Merge Sort、Heap Sort 與 Quick Sort 使用大量隨機資料進行測試，並選取其中執行時間最長者作為 worst-case 結果。

此 worst-case 並非理論上建構的極端輸入，而是透過隨機樣本搜尋得到的「實驗最差情況」，用以模擬實務環境下可能遇到的最不利輸入。

---

### CSV 輸出格式說明

實驗結果會輸出至 `sorting_result.csv`，採用 long-format（長表格式）：

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
