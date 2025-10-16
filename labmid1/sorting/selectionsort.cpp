#include<iostream>
using namespace std;

void ss(int arr[],int n){

    for (int i = 0; i < n-1 ; i++)
    {
        int minI = i;
        for (int j = i+1; j < n; j++)
        {
            if(arr[j]<arr[minI]){
                minI=j;
            }
        }
        swap(arr[i],arr[minI]);
    }
    

}

int main(){
    int n=6;
    int arr[6]={3,5,6,1,8,4}; 

    ss(arr,n);
    for (int i = 0; i < n; i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    
    return 0;
}