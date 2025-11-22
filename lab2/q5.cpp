#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter the size of the matrices (N x N): ";
    cin >> n;

    int** matrix1 = new int*[n];
    int** matrix2 = new int*[n];
    int** result = new int*[n];

    for (int i = 0; i < n; ++i) {
        matrix1[i] = new int[n];
        matrix2[i] = new int[n];
        result[i] = new int[n];
    }

    cout << "Enter elements of Matrix 1:\n";
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> matrix1[i][j];

    cout << "Enter elements of Matrix 2:\n";
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> matrix2[i][j];

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            result[i][j] = matrix1[i][j] - matrix2[i][j];

    cout << "Resulting matrix after subtraction:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            cout << result[i][j] << " ";
        cout << endl;
    }

    for (int i = 0; i < n; ++i) {
        delete[] matrix1[i];
        delete[] matrix2[i];
        delete[] result[i];
    }
    delete[] matrix1;
    delete[] matrix2;
    delete[] result;

    return 0;
}
