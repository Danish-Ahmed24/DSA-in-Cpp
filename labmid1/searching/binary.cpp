#include<iostream>
using namespace std;

void binarySearch(int arr[],int n,int target){
    int left =0 , right = n-1;
    while(left<=right){
        int mid = (left+right)/2;   

        if(arr[mid] == target){
            cout<<"found at"<< mid<<endl;
            return;
        }
        else if(arr[mid] < target){
            left = mid+1;
        }
        else {
            right = mid-1;
        }
    }
    cout<<"not found"<<endl;
}

int main(){
    int n=6;
    int arr[6]={3,5,6,1,8,4}; 

    binarySearch(arr,n,6);
    cout<<endl;
    
    return 0;
}