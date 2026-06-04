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
