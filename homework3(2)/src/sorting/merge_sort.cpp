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
    int i = left;
    int j = mid + 1;
    int k = left;

    while(i <= mid && j <= right)
    {
        if(arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while(i <= mid)
        temp[k++] = arr[i++];

    while(j <= right)
        temp[k++] = arr[j++];

    for(int p = left; p <= right; p++)
        arr[p] = temp[p];
}

void iterativeMergeSort(int arr[], int n)
{
    int* temp = new int[n];

    for(int size = 1; size < n; size *= 2)
    {
        for(int left = 0;
            left < n - 1;
            left += 2 * size)
        {
            int mid = left + size - 1;

            if(mid >= n - 1)
                continue;

            int right = left + 2 * size - 1;

            if(right >= n)
                right = n - 1;

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
