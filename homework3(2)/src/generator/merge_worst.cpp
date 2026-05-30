//41343133
//41343122
#include <iostream>
using namespace std;

// 遞迴產生 Merge Sort Worst Case
void generateMergeWorstCase(int arr[], int left, int right)
{
    if(right - left <= 1)
        return;

    int size = right - left + 1;

    int* temp = new int[size];

    int index = 0;

    // 奇數位置
    for(int i = left; i <= right; i += 2)
    {
        temp[index++] = arr[i];
    }

    // 偶數位置
    for(int i = left + 1; i <= right; i += 2)
    {
        temp[index++] = arr[i];
    }

    // 複製回去
    for(int i = 0; i < size; i++)
    {
        arr[left + i] = temp[i];
    }

    delete[] temp;

    int mid = (left + right) / 2;

    generateMergeWorstCase(arr, left, mid);
    generateMergeWorstCase(arr, mid + 1, right);
}

int main()
{
    int n;

    cin >> n;

    int* arr = new int[n];

    // 初始化 1~n
    for(int i = 0; i < n; i++)
    {
        arr[i] = i + 1;
    }

    generateMergeWorstCase(arr, 0, n - 1);

    cout << "Merge Sort Worst Case:\n";

    for(int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;

    delete[] arr;

    return 0;
}
