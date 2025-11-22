#include <iostream>
using namespace std;

// int binarySearch(int arr[], int n, int target) {
//     int low = 0, high = n - 1;

//     while (low <= high) {
//         int mid = low + (high - low) / 2;  // Prevent overflow

//         if (arr[mid] == target)
//             return mid;  // Found
//         else if (arr[mid] < target)
//             low = mid + 1;  // Search right half
//         else
//             high = mid - 1; // Search left half
//     }
//     return -1;  // Not found
// }
int binarySearch(int arr[], int n, int target) {
    int low =0 , high = n-1;
    while(low<=high){
        int mid = low + (high-low)/2;
        if(arr[mid]==target){
            return mid;
        }else if(arr[mid]>target){
            high = mid -1;
        }else if(arr[mid]<target){
            low =mid + 1
        }
    }
    return -1;
}

int main() {
    int arr[] = {10, 20, 30, 40, 50}; 
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 40;

    int result = binarySearch(arr, n, target);

    if (result != -1)
        cout << "Element found at index " << result;
    else
        cout << "Element not found";
}
// 1.3 comb buble selection insertion 