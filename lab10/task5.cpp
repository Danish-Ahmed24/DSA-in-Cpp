#include <iostream>
using namespace std;

class MinHeap {
private:
    int* heap;
    int capacity;
    int size;
    
    void heapifyDown(int index) {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        
        if (left < size && heap[left] < heap[smallest]) {
            smallest = left;
        }
        
        if (right < size && heap[right] < heap[smallest]) {
            smallest = right;
        }
        
        if (smallest != index) {
            int temp = heap[index];
            heap[index] = heap[smallest];
            heap[smallest] = temp;
            heapifyDown(smallest);
        }
    }
    
public:
    MinHeap(int cap) {
        capacity = cap;
        size = 0;
        heap = new int[capacity];
    }
    
    ~MinHeap() {
        delete[] heap;
    }
    
    void buildHeap(int* arr, int n) {
        size = n;
        if (size > capacity) {
            delete[] heap;
            capacity = size;
            heap = new int[capacity];
        }
        
        for (int i = 0; i < n; i++) {
            heap[i] = arr[i];
        }
        
        for (int i = (n / 2) - 1; i >= 0; i--) {
            heapifyDown(i);
        }
    }
    
    void printHeap() {
        for (int i = 0; i < size; i++) {
            cout << heap[i];
            if (i < size - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
    
    int extractMin() {
        if (size == 0) {
            return -1;
        }
        
        int minValue = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);
        
        return minValue;
    }
    
    int getMin() {
        if (size == 0) {
            return -1;
        }
        return heap[0];
    }
    
    bool isEmpty() {
        return size == 0;
    }
};

class DeliveryScheduler {
public:
    void organizeDeliveries(int* packages, int n, MinHeap& minHeap) {
        minHeap.buildHeap(packages, n);
    }
};

int main() {
    int n;
    cout << "Enter number of packages: ";
    cin >> n;
    
    int* packages = new int[n];
    cout << "Enter delivery times: ";
    for (int i = 0; i < n; i++) {
        cin >> packages[i];
    }
    
    MinHeap minHeap(n);
    DeliveryScheduler scheduler;
    
    scheduler.organizeDeliveries(packages, n, minHeap);
    
    cout << "Min-heap of delivery times: ";
    minHeap.printHeap();
    
    delete[] packages;
    
    return 0;
}