#include<iostream>
using namespace std;

void quickSort(int arr[],int start,int end){
    if(start>=end) return;

    int pivot = partition(arr,start,end);
    quickSort(arr,start,pivot-1);
    quickSort(arr,pivot+1,end);
}

int partition(int arr[],int start,int end){
    int i = start-1;
    int pivot = arr[end];
    for(int j = start ; j<end;j++){
        if(arr[j]<pivot){
            i++;
            swap(arr[i],arr[j]);
        }
    }
    i++;
    swap(arr[i],arr[end]);
    return i;
}

int main()
{
    int arr[] = {3,5,2,3,6,2,31};
    quickSort(arr,0,7-1);
    return 0;
}