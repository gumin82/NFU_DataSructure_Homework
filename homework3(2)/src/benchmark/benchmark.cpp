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
// Fastest record
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
// correctness check
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
// copy
//========================
void copyArray(int src[], int dst[], int n)
{
    for (int i = 0; i < n; i++)
        dst[i] = src[i];
}

//========================
// measure (TIME + MEMORY)
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
    fout.close();
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
            if (c == 0) generateBestCase(original, n);
            else if (c == 1) generateAverageCase(original, n);
            else generateWorstCase(original, n);

            cout << "\nN=" << n << " Case=" << cases[c] << "\n";

            string bestName = "";
            double bestTime = 1e18;

            //========================
            // Insertion
            //========================
            copyArray(original, data, n);
            auto r = measureSort(insertionSort, data, n);

            cout << "Insertion : " << r.first << " us | " << r.second << " KB\n";
            records.push_back({ n, cases[c], "InsertionSort", r.first, r.second });

            if (r.first < bestTime)
                bestTime = r.first, bestName = "InsertionSort";

            //========================
            // Quick
            //========================
            copyArray(original, data, n);
            r = measureSort(quickSort, data, n);

            cout << "Quick     : " << r.first << " us | " << r.second << " KB\n";
            records.push_back({ n, cases[c], "QuickSort", r.first, r.second });

            if (r.first < bestTime)
                bestTime = r.first, bestName = "QuickSort";

            //========================
            // Merge
            //========================
            copyArray(original, data, n);
            r = measureSort(mergeSort, data, n);

            cout << "Merge     : " << r.first << " us | " << r.second << " KB\n";
            records.push_back({ n, cases[c], "MergeSort", r.first, r.second });

            if (r.first < bestTime)
                bestTime = r.first, bestName = "MergeSort";

            //========================
            // Heap
            //========================
            copyArray(original, data, n);
            r = measureSort(heapSort, data, n);

            cout << "Heap      : " << r.first << " us | " << r.second << " KB\n";
            records.push_back({ n, cases[c], "HeapSort", r.first, r.second });

            if (r.first < bestTime)
                bestTime = r.first, bestName = "HeapSort";

            //========================
            // Composite
            //========================
            copyArray(original, data, n);
            r = measureSort(compositeSort, data, n);

            cout << "Composite : " << r.first << " us | " << r.second << " KB\n";
            records.push_back({ n, cases[c], "CompositeSort", r.first, r.second });

            if (r.first < bestTime)
                bestTime = r.first, bestName = "CompositeSort";

            //========================
            // fastest summary
            //========================
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
