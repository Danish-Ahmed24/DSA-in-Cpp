#include <iostream>
using namespace std;

class Element {
public:
    int value;
    int frequency;
    
    Element() {
        value = 0;
        frequency = 0;
    }
    
    Element(int v, int f) {
        value = v;
        frequency = f;
    }
};

class MaxHeap {
private:
    Element* heap;
    int capacity;
    int size;
    
    void heapifyDown(int index) {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        
        if (left < size) {
            if (heap[left].frequency > heap[largest].frequency) {
                largest = left;
            } else if (heap[left].frequency == heap[largest].frequency && heap[left].value > heap[largest].value) {
                largest = left;
            }
        }
        
        if (right < size) {
            if (heap[right].frequency > heap[largest].frequency) {
                largest = right;
            } else if (heap[right].frequency == heap[largest].frequency && heap[right].value > heap[largest].value) {
                largest = right;
            }
        }
        
        if (largest != index) {
            Element temp = heap[index];
            heap[index] = heap[largest];
            heap[largest] = temp;
            heapifyDown(largest);
        }
    }
    
    void heapifyUp(int index) {
        int parent = (index - 1) / 2;
        
        if (index > 0) {
            bool shouldSwap = false;
            if (heap[index].frequency > heap[parent].frequency) {
                shouldSwap = true;
            } else if (heap[index].frequency == heap[parent].frequency && heap[index].value > heap[parent].value) {
                shouldSwap = true;
            }
            
            if (shouldSwap) {
                Element temp = heap[index];
                heap[index] = heap[parent];
                heap[parent] = temp;
                heapifyUp(parent);
            }
        }
    }
    
public:
    MaxHeap(int cap) {
        capacity = cap;
        size = 0;
        heap = new Element[capacity];
    }
    
    ~MaxHeap() {
        delete[] heap;
    }
    
    void insert(Element elem) {
        if (size == capacity) {
            return;
        }
        heap[size] = elem;
        heapifyUp(size);
        size++;
    }
    
    Element extractMax() {
        if (size == 0) {
            return Element(-1, -1);
        }
        
        Element maxElem = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);
        
        return maxElem;
    }
    
    bool isEmpty() {
        return size == 0;
    }
};

class TopKFrequent {
public:
    int* findTopK(int* arr, int n, int k, int& resultSize) {
        int* freq = new int[100001];
        for (int i = 0; i < 100001; i++) {
            freq[i] = 0;
        }
        
        int minVal = arr[0];
        int maxVal = arr[0];
        for (int i = 0; i < n; i++) {
            freq[arr[i]]++;
            if (arr[i] < minVal) minVal = arr[i];
            if (arr[i] > maxVal) maxVal = arr[i];
        }
        
        MaxHeap maxHeap(maxVal - minVal + 1);
        
        for (int i = minVal; i <= maxVal; i++) {
            if (freq[i] > 0) {
                Element elem(i, freq[i]);
                maxHeap.insert(elem);
            }
        }
        
        resultSize = k;
        int* result = new int[k];
        
        for (int i = 0; i < k && !maxHeap.isEmpty(); i++) {
            Element top = maxHeap.extractMax();
            result[i] = top.value;
        }
        
        delete[] freq;
        return result;
    }
};

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    
    int* arr = new int[n];
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    int k;
    cout << "Enter k: ";
    cin >> k;
    
    TopKFrequent finder;
    int resultSize;
    int* result = finder.findTopK(arr, n, k, resultSize);
    
    cout << "Top " << k << " frequent elements: ";
    for (int i = 0; i < resultSize; i++) {
        cout << result[i];
        if (i < resultSize - 1) {
            cout << " ";
        }
    }
    cout << endl;
    
    delete[] arr;
    delete[] result;
    
    return 0;
}