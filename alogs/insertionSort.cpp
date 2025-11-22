#include<iostream>
using namespace std;

void printArray(int arr[],int size){
    for(int i =0 ; i< size;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}
void insertionSort(int arr[],int size){
    for(int i = 1 ; i < size ; i++){
        int taken = i;
        int key= arr[taken];
        int j = i-1;
        while(j>=0 && key<arr[j]){
            arr[j+1] = arr[j];
            j--;
            printArray(arr,size);
        }
        arr[j+1]=key;
    }

}


int main()
{
    int arr[]={7,4,-3,1,0,6};
    int size = sizeof(arr)/sizeof(arr[0]);
    insertionSort(arr,size);
    printArray(arr,size);
}