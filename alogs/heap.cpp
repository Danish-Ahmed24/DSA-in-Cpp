#include<iostream>
using namespace std;

class Heap{
    int arr[100];
    int size = 0;
    public:
        Heap(){

        }

        
    void insert(int val){
        size++;
        int index = size;
        arr[index] = val;

        while(index>1){
            int parent = index/2;

            if(arr[parent]<arr[index]){
                swap(arr[parent],arr[index]);
                index = parent;
            }
            else
                return;
        }
    }

    void deleteKar(){
        if(size == 0){
            cout<<"Nothing to delete";
            return;
        }
        //put last element to first position
        arr[1] = arr[size];
        //last element ka bubble pop kardo
        size--;
        // take root note to its correct position
        int i = 1;
        while(i < size){
            int left = i*2;
            int right = i*2 + 1;
            if(left < size && arr[i]<arr[left]){
                swap(arr[i],arr[left]);
                i = left;
            }
            else if(right < size && arr[i]<arr[right]){
                swap(arr[i],arr[right]);
                i = right;
            }
            else{
                return ;
            }
        }

    }

    

    void print(){
        for (int i = 1; i <= size; i++)
        {
            cout<<arr[i]<<" ";
        }
        cout<<endl;
        
    }
};

void heapSort(int arr[],int n){
    int t = n;

    while(t > 1){
        //step 1
        swap(arr[t],arr[1]);
        t--;
        heapify(arr,n,1);
    }
}

void heapify(int arr[] , int n ,int i){
        int largest = i;
        int left = i*2;
        int right = i*2 +1;

        if(left<=n && arr[largest] < arr[left]){
            largest = left;
        }
        if (right<=n && arr[largest]<arr[right]){
            largest = right;
        }

        if(largest != i){
            swap(arr[i],arr[largest]);
            heapify(arr,n,largest);
        }
    }


    int main()
{
    // Heap h;
    // h.insert(50);
    // h.insert(55);
    // h.insert(53);
    // h.insert(52);
    // h.insert(54);
    // h.print();
    // h.deleteKar();
    // h.print();
    int arr[6] = {-1,3,7,4,2,6};
    int n = 6-1;
    for(int i = n/2 ;i > 0; i--){
        heapify(arr,n,i);
    }
    for (int i = 1; i <= n; i++)
        {
            cout<<arr[i]<<" ";
        }
        cout<<endl;
}