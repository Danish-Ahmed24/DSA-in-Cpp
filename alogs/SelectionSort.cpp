#include<iostream>
using namespace std;

void selectionSort(int arr[],int size){
    for(int i =0 ; i < size-1 ; i++){
        int min = i;
        for(int j=i;j<size;j++){
            if(arr[min]>arr[j]){
                min = j;
            }
        }
        swap(arr[min],arr[i]);
    }
}

void printArray(int arr[],int size){
    for(int i =0 ; i< size;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

int main()
{
    int arr[] = {3,5,-2,4,0,1};
    int size = sizeof(arr)/sizeof(arr[0]);

    selectionSort(arr,size);
    printArray(arr,size);
}