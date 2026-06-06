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
