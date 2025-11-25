#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int *arr = new int[n];
    int i = 0;
    while (i < n) {
        cin >> arr[i];
        i++;
    }

    int range = n;
    int *hash = new int[range];
    i = 0;
    while (i < range) {
        hash[i] = 0;
        i++;
    }

    i = 0;
    int duplicate = -1;
    while (i < n) {
        int val = arr[i];
        if (hash[val] == 1) {
            duplicate = val;
            break;
        } else {
            hash[val] = 1;
        }
        i++;
    }

    cout <<"duplicate: " <<duplicate;

    delete[] arr;
    delete[] hash;

    return 0;
}
