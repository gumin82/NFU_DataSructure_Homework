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
