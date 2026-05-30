
#include <iostream>
using namespace std;

void merge(int arr[],
           int temp[],
           int leftStart,
           int rightStart,
           int rightEnd)
{
    int leftEnd=rightStart-1;
    int tempPos=leftStart;

    while(leftStart<=leftEnd &&
          rightStart<=rightEnd)
    {
        if(arr[leftStart]<=arr[rightStart])
            temp[tempPos++]=arr[leftStart++];
        else
            temp[tempPos++]=arr[rightStart++];
    }

    while(leftStart<=leftEnd)
        temp[tempPos++]=arr[leftStart++];

    while(rightStart<=rightEnd)
        temp[tempPos++]=arr[rightStart++];

    for(int i=0;i<=rightEnd;i++)
        arr[i]=temp[i];
}

void iterativeMergeSort(int arr[],int n)
{
    int* temp=new int[n];

    for(int size=1;size<n;size*=2)
    {
        for(int left=0;
            left<n-1;
            left+=2*size)
        {
            int mid=left+size-1;

            int right=
            left+2*size-1;

            if(mid>=n-1)
                continue;

            if(right>=n)
                right=n-1;

            merge(arr,temp,left,
                  mid+1,right);
        }
    }

    delete[] temp;
}

int main()
{
    int n;
    cin>>n;

    int* arr=new int[n];

    for(int i=0;i<n;i++)
        cin>>arr[i];

    iterativeMergeSort(arr,n);

    for(int i=0;i<n;i++)
        cout<<arr[i]<<" ";

    cout<<endl;

    delete[] arr;

    return 0;
}
