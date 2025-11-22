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
    
    void heapifyUp(int index) {
        int parent = (index - 1) / 2;
        
        if (index > 0 && heap[index] < heap[parent]) {
            int temp = heap[index];
            heap[index] = heap[parent];
            heap[parent] = temp;
            heapifyUp(parent);
        }
    }
    
public:
    MinHeap(int cap) {
        capacity = cap;
        size = 0;
        heap = new int[capacity];
    }
    
    MinHeap(int* arr, int n) {
        capacity = n;
        size = n;
        heap = new int[capacity];
        
        for (int i = 0; i < n; i++) {
            heap[i] = arr[i];
        }
        
        for (int i = (n / 2) - 1; i >= 0; i--) {
            heapifyDown(i);
        }
    }
    
    ~MinHeap() {
        delete[] heap;
    }
    
    void insert(int value) {
        if (size == capacity) {
            int* newHeap = new int[capacity * 2];
            for (int i = 0; i < size; i++) {
                newHeap[i] = heap[i];
            }
            delete[] heap;
            heap = newHeap;
            capacity = capacity * 2;
        }
        
        heap[size] = value;
        heapifyUp(size);
        size++;
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
    
    int getSize() {
        return size;
    }
    
    int* getHeapArray() {
        return heap;
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
};

class HeapMerger {
public:
    MinHeap* mergeHeaps(int* heap1, int size1, int* heap2, int size2) {
        int totalSize = size1 + size2;
        int* mergedArray = new int[totalSize];
        
        for (int i = 0; i < size1; i++) {
            mergedArray[i] = heap1[i];
        }
        
        for (int i = 0; i < size2; i++) {
            mergedArray[size1 + i] = heap2[i];
        }
        
        MinHeap* mergedHeap = new MinHeap(mergedArray, totalSize);
        
        delete[] mergedArray;
        return mergedHeap;
    }
};

int main() {
    int n1;
    cout << "Enter number of deliveries in branch 1: ";
    cin >> n1;
    
    int* heap1 = new int[n1];
    cout << "Enter delivery times for branch 1: ";
    for (int i = 0; i < n1; i++) {
        cin >> heap1[i];
    }
    
    int n2;
    cout << "Enter number of deliveries in branch 2: ";
    cin >> n2;
    
    int* heap2 = new int[n2];
    cout << "Enter delivery times for branch 2: ";
    for (int i = 0; i < n2; i++) {
        cin >> heap2[i];
    }
    
    HeapMerger merger;
    MinHeap* mergedHeap = merger.mergeHeaps(heap1, n1, heap2, n2);
    
    cout << "Merged min-heap: ";
    mergedHeap->printHeap();
    
    delete[] heap1;
    delete[] heap2;
    delete mergedHeap;
    
    return 0;
}