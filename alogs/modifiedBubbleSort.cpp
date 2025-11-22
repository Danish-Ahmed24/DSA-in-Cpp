#include<iostream>
using namespace std;

void bubbleSort(int arr[],int size){
    for(int i=0;i<size-1;i++){
        bool flag = false;
        for (int j = 0; j < size-i-1; j++)
        {
            if(arr[j]>arr[j+1])
            {
                flag = true;
                swap(arr[j],arr[j+1]);
            }
        }
        if(!flag) break;
        
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
    int arr[]={4,2,6,1,5,-1};
    int size = sizeof(arr)/sizeof(arr[0]);
    bubbleSort(arr,size);
    printArray(arr,size);


}