#include <iostream>
using namespace std;

void heapify(int heap[], int n, int i) {
    int smallest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;
    if(l < n && heap[l] < heap[smallest]) {
        smallest = l;
    }
    if(r < n && heap[r] < heap[smallest]) {
        smallest = r;
    }
    if(smallest != i) {
        int temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;
        heapify(heap, n, smallest);
    }
}

int extractMin(int heap[], int &n) {
    int minVal = heap[0];
    heap[0] = heap[n-1];
    n--;
    heapify(heap, n, 0);
    return minVal;
}

void insertHeap(int heap[], int &n, int val) {
    n++;
    int i = n-1;
    heap[i] = val;
    while(i != 0 && heap[(i-1)/2] > heap[i]) {
        int temp = heap[i];
        heap[i] = heap[(i-1)/2];
        heap[(i-1)/2] = temp;
        i = (i-1)/2;
    }
}

int main() {
    int arr[] = {4,2,7,6,9};
    int n = 5;
    int heap[100];
    for(int i=0;i<n;i++) {
        heap[i] = arr[i];
    }
    for(int i=n/2-1;i>=0;i--) {
        heapify(heap,n,i);
    }

    int totalCost = 0;
    int size = n;
    while(size > 1) {
        int a = extractMin(heap, size);
        int b = extractMin(heap, size);
        int cost = a + b;
        totalCost += cost;
        insertHeap(heap, size, cost);
    }

    cout << totalCost << endl;
    return 0;
}
