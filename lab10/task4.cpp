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
    
    void buildMinHeap(int* arr, int n) {
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
    
    int getSize() {
        return size;
    }
};

class HeapConverter {
public:
    void convertMaxToMin(int* maxHeap, int n, MinHeap& minHeap) {
        minHeap.buildMinHeap(maxHeap, n);
    }
};

int main() {
    int n;
    cout << "Enter number of tasks: ";
    cin >> n;
    
    int* maxHeap = new int[n];
    cout << "Enter max-heap array: ";
    for (int i = 0; i < n; i++) {
        cin >> maxHeap[i];
    }
    
    MinHeap minHeap(n);
    HeapConverter converter;
    
    converter.convertMaxToMin(maxHeap, n, minHeap);
    
    cout << "Converted min-heap: ";
    minHeap.printHeap();
    
    delete[] maxHeap;
    
    return 0;
}