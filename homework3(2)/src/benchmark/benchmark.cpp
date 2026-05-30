//41343133
//41343122
#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

/*
====================================
暫時測試用排序函式
之後改成你的 sorting
====================================
*/
void testSort(int arr[], int n)
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

/*
====================================
暫時測試用 Worst Case
之後改成 Generator
====================================
*/
void generateWorstCase(int arr[], int n)
{
    for(int i = 0; i < n; i++)
    {
        arr[i] = n - i;
    }
}

/*
====================================
計時
====================================
*/
double measureTime(int arr[], int n)
{
    auto start = high_resolution_clock::now();

    testSort(arr, n);

    auto end = high_resolution_clock::now();

    duration<double> elapsed = end - start;

    return elapsed.count();
}

/*
====================================
Benchmark
====================================
*/
int main()
{
    int testSize[] =
    {
        500,
        1000,
        2000,
        3000,
        4000,
        5000
    };

    cout << "n\tTime(sec)" << endl;

    for(int k = 0; k < 6; k++)
    {
        int n = testSize[k];

        int* arr = new int[n];

        generateWorstCase(arr, n);

        double runtime =
            measureTime(arr, n);

        cout << n
             << "\t"
             << runtime
             << endl;

        delete[] arr;
    }

    return 0;
}
