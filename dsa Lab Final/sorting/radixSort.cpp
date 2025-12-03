#include <iostream>
#include <vector>
using namespace std;


void countSort(int arr[],int n,int rep){
    int output[100];
    int count[10]={0};

    for(int i =0 ; i < n ;i++){
        int digit = (arr[i] /rep)%10;
        count[digit]++;
    }

    for(int i =1 ; i<10 ; i++){
        int digit = (arr[i]/rep)%10;
        count[i] += count[i-1];
    }
    
    for(int i=n-1;i>0;i--){
        int digit = (arr[i]/rep)%10;
        output[count[digit]-1]=arr[i];
        count[digit]--;
    }

    for(int i =0 ; i<n;i++){
        arr[i]=output[i];
    }

}



void radixSort(int arr[],int n){
    int maxVal = arr[0];
    for(int i=0;i<n;i++){
        if(maxVal<arr[i]){
            maxVal=arr[i];
        }
    }

    for(int rep = 1 ; maxVal/rep >=0 ; rep*=10){
        countSort(arr,n,rep);
    }
}

int main() {
    // vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};

    // radixSort(arr);

    // for (int x : arr)
        // cout << x << " ";
}
