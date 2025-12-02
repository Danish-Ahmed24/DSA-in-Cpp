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

class Heap{ 
    public:
    int size = 0;
    int capacity = 100;
    int arr[100];


    void remove(){
        if(size<=0){
            cout<<"underflow"<<endl;
        }

        if(size==1){
            size--;
            return;
        }

        arr[0]=arr[size-1];
        size--;
        heapify(arr,size,0);
    }
    void insertMax(int val){
        if(size== capacity){
            cout<<"overflow"<<endl;
        }
        if(size==1){
            size--;
            return;
        }

        size++;
        int i = size;
        arr[i]=val;

        while(i>0){
            int parent = (i-1)/2;

            if(arr[parent]<arr[i]){
                swap(arr[parent],arr[i]);
                i = parent;
            }else{return;}

        }
    }
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