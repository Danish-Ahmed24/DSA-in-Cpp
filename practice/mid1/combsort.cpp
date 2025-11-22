#include <iostream>
using namespace std;

void combSort(int arr[], int n) {
    int gap = n;
    bool swapped = true;

    while (gap > 1 || swapped) {
        // Update gap
        gap = (gap * 10) / 13; // equivalent to gap / 1.3
        if (gap < 1) gap = 1;

        swapped = false;

        for (int i = 0; i + gap < n; i++) {
            if (arr[i] > arr[i + gap]) {
                swap(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
    }
}

int main() {
    int arr[] = {14, 4, 2, 6, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    combSort(arr, n);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
}
