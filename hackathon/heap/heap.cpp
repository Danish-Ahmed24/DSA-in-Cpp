#include<iostream>
using namespace std;

class Heap{
    public:
    int size = 0;
    int capacity = 100;
    int arr[100];

    void insert(int val){
        if(size == capacity){
            cout<<"overflow";
            return;
        }

        size++;
        int i = size;
        arr[i]=val;

        while(i>0){
            int parent = (i-1)/2;

            if(arr[parent]>arr[i]){
                swap(arr[parent],arr[i]);
                i = parent;
            }
            else{
                return;
            }

        }
    }
};


int main()
{
    
}