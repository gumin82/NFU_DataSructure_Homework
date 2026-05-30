//41343133
//41343122
#include <iostream>
using namespace std;

void swapValue(int &a,int &b)
{
    int temp=a;
    a=b;
    b=temp;
}

int medianOfThree(int arr[],int left,int right)
{
    int mid=(left+right)/2;

    if(arr[left]>arr[mid])
        swapValue(arr[left],arr[mid]);

    if(arr[left]>arr[right])
        swapValue(arr[left],arr[right]);

    if(arr[mid]>arr[right])
        swapValue(arr[mid],arr[right]);

    swapValue(arr[mid],arr[right-1]);

    return arr[right-1];
}

void quickSort(int arr[],int left,int right)
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
                swapValue(arr[i],arr[j]);
            else
                break;
        }

        swapValue(arr[i],arr[right-1]);

        quickSort(arr,left,i-1);
        quickSort(arr,i+1,right);
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

int main()
{
    int n;
    cin>>n;

    int* arr=new int[n];

    for(int i=0;i<n;i++)
        cin>>arr[i];

    quickSort(arr,0,n-1);

    for(int i=0;i<n;i++)
        cout<<arr[i]<<" ";

    cout<<endl;

    delete[] arr;

    return 0;
}
