#include<iostream>
using namespace std;

void heapify(int arr[],int size , int i){
    int smallest = i;
    int left = i*2+1;
    int right = i*2+2;

    if(left<size && arr[left]<arr[smallest]){
        smallest = left;
    }
    if(right<size && arr[right]<arr[smallest]){
        smallest = right;
    }

    if(smallest != i){
        swap(arr[smallest],arr[i]);
        heapify(arr,size,smallest);
    } 
}





int main()
{
    
}