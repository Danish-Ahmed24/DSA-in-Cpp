#include<iostream>
using namespace std;

void heapify(int arr[],int size,int i){
    int largest = i;
    int left = i*2+1;
    int right = i*2+2;

    if(left<size && arr[left]>arr[largest]){
        largest = left;
    }
    if(right<size && arr[right]>arr[largest]){
        largest = right;
    }

    if(largest != i){
        swap(arr[i],arr[largest]);
        heapify(arr,size,largest);
    } 
}













int main()
{
    
}