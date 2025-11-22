#include<iostream>
using namespace std;

void insertionSort(int arr[],int n){
    for (int i = 1; i < n; i++)
    {
        int current = arr[i];
        int j=i-1;
        while(j>=0 && arr[j]>current){
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=current;
    }
    
    
}

int main(){
    int arr[]={1,54,32,2};
    int n = sizeof(arr)/sizeof(arr[0]);
    insertionSort(arr, n);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
}