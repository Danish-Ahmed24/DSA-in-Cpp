#include<iostream>
using namespace std;

void selectionSort(int arr[],int n){
    for (int i = 0; i < n; i++)
    {
        int min = i;
        for (int  j = i+1; j < n; j++)
        {
            if(arr[min]>arr[j]){
                min = j;
            }
        }
        if(min!=i){
            int temp = arr[min];
            arr[min]=arr[i];
            arr[i]=temp;
        }
        
    }
    
}
int main(){
    int arr[]={1,54,32,2};
    int n = sizeof(arr)/sizeof(arr[0]);
    selectionSort(arr, n);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
}
/*
    3253

*/