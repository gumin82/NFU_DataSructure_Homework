//41343133
//41343122
#include <iostream>
using namespace std;

// Insertion Sort Worst Case
void generateInsertionWorstCase(int arr[], int n)
{
    for(int i = 0; i < n; i++)
    {
        arr[i] = n - i;
    }
}

// 測試用
int main()
{
    int n;

    cin >> n;

    int* arr = new int[n];

    generateInsertionWorstCase(arr, n);

    cout << "Insertion Sort Worst Case:\n";

    for(int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;

    delete[] arr;

    return 0;
}
