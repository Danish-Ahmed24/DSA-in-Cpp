#include<iostream>
#include<queue>
using namespace std;

int kthSmallest(int arr[],int l,int r,int k){
    //insert in maxheap
    priority_queue<int> pq;
    for(int i = l ; i <k ; i++){
        pq.push(arr[i]);
    }

    for(int i = k ; i <=r;i++){
        if(pq.top()>arr[i]){
            pq.pop();
            pq.push(arr[i]);
        }
    }

    return pq.top();
}
    
int main()
{
    int arr[]={3,5,4,7,1,0};
    int size = sizeof(arr)/sizeof(arr[0]);
    int e = kthSmallest(arr,0,size-1,3);
    cout<<e;
    return 0;
}