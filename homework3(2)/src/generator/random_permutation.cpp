//41343133
//41343122
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Random Permutation Generator
void generateRandomPermutation(int arr[], int n)
{
    // 初始化
    for(int i = 0; i < n; i++)
    {
        arr[i] = i + 1;
    }

    // Fisher-Yates Shuffle
    for(int i = n - 1; i >= 1; i--)
    {
        int j = rand() % (i + 1);

        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

int main()
{
    srand((unsigned)time(NULL));

    int n;

    cin >> n;

    int* arr = new int[n];

    generateRandomPermutation(arr, n);

    cout << "Random Permutation:\n";

    for(int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;

    delete[] arr;

    return 0;
}
