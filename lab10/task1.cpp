#include <iostream>
using namespace std;

class HeapNode {
public:
    int value;
    int arrayIndex;
    int elementIndex;
    
    HeapNode() {
        value = 0;
        arrayIndex = 0;
        elementIndex = 0;
    }
    
    HeapNode(int v, int ai, int ei) {
        value = v;
        arrayIndex = ai;
        elementIndex = ei;
    }
};

class MinHeap {
private:
    HeapNode* heap;
    int capacity;
    int size;
    
    void heapifyDown(int index) {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        
        if (left < size && heap[left].value < heap[smallest].value) {
            smallest = left;
        }
        
        if (right < size && heap[right].value < heap[smallest].value) {
            smallest = right;
        }
        
        if (smallest != index) {
            HeapNode temp = heap[index];
            heap[index] = heap[smallest];
            heap[smallest] = temp;
            heapifyDown(smallest);
        }
    }
    
    void heapifyUp(int index) {
        int parent = (index - 1) / 2;
        
        if (index > 0 && heap[index].value < heap[parent].value) {
            HeapNode temp = heap[index];
            heap[index] = heap[parent];
            heap[parent] = temp;
            heapifyUp(parent);
        }
    }
    
public:
    MinHeap(int cap) {
        capacity = cap;
        size = 0;
        heap = new HeapNode[capacity];
    }
    
    ~MinHeap() {
        delete[] heap;
    }
    
    void insert(HeapNode node) {
        if (size == capacity) {
            return;
        }
        heap[size] = node;
        heapifyUp(size);
        size++;
    }
    
    HeapNode extractMin() {
        if (size == 0) {
            return HeapNode(-1, -1, -1);
        }
        
        HeapNode minNode = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);
        
        return minNode;
    }
    
    bool isEmpty() {
        return size == 0;
    }
};

class MergeKSorted {
public:
    int* mergeArrays(int** arrays, int* sizes, int k, int& resultSize) {
        resultSize = 0;
        for (int i = 0; i < k; i++) {
            resultSize += sizes[i];
        }
        
        int* result = new int[resultSize];
        MinHeap minHeap(k);
        
        for (int i = 0; i < k; i++) {
            if (sizes[i] > 0) {
                HeapNode node(arrays[i][0], i, 0);
                minHeap.insert(node);
            }
        }
        
        int resultIndex = 0;
        while (!minHeap.isEmpty()) {
            HeapNode minNode = minHeap.extractMin();
            result[resultIndex++] = minNode.value;
            
            int nextIndex = minNode.elementIndex + 1;
            if (nextIndex < sizes[minNode.arrayIndex]) {
                HeapNode nextNode(arrays[minNode.arrayIndex][nextIndex], minNode.arrayIndex, nextIndex);
                minHeap.insert(nextNode);
            }
        }
        
        return result;
    }
};

int main() {
    int k;
    cout << "Enter number of servers: ";
    cin >> k;
    
    int** arrays = new int*[k];
    int* sizes = new int[k];
    
    for (int i = 0; i < k; i++) {
        cout << "Enter number of patients in server " << i + 1 << ": ";
        cin >> sizes[i];
        arrays[i] = new int[sizes[i]];
        cout << "Enter admission times: ";
        for (int j = 0; j < sizes[i]; j++) {
            cin >> arrays[i][j];
        }
    }
    
    MergeKSorted merger;
    int resultSize;
    int* result = merger.mergeArrays(arrays, sizes, k, resultSize);
    
    cout << "Merged patient list: ";
    for (int i = 0; i < resultSize; i++) {
        cout << result[i];
        if (i < resultSize - 1) {
            cout << " ";
        }
    }
    cout << endl;
    
    for (int i = 0; i < k; i++) {
        delete[] arrays[i];
    }
    delete[] arrays;
    delete[] sizes;
    delete[] result;
    
    return 0;
}