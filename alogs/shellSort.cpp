#include<iostream>
using namespace std;

void printArray(int arr[],int size){
    for(int i =0 ; i< size;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

void shellSort(int arr[], int size){
    for(int gap = size/2; gap > 0; gap /= 2){
        for(int i = gap; i < size; i++){
            int key = arr[i];
            int j = i;

            while(j >= gap && arr[j - gap] > key){
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = key;
        }
    }
}

int main()
{
    int arr[] = {2,5,3,-1,0};
    int size = sizeof(arr)/sizeof(arr[0]);

    shellSort(arr,size);
    printArray(arr,size);
}