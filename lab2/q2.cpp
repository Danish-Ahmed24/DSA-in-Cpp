#include <iostream>
using namespace std;

int main() {
    int members;
    cout << "Enter number of members: ";
    cin >> members;

    int** borrowedBooks = new int*[members];
    int* bookCounts = new int[members];

    for (int i = 0; i < members; ++i) {
        cout << "Enter number of books borrowed by member " << i + 1 << ": ";
        cin >> bookCounts[i];
        borrowedBooks[i] = new int[bookCounts[i]];

        cout << "Enter book IDs for member " << i + 1 << ":\n";
        for (int j = 0; j < bookCounts[i]; ++j) {
            cin >> borrowedBooks[i][j];
        }
    }

    for (int i = 0; i < members; ++i) {
        cout << "Member " << i + 1 << " borrowed " << bookCounts[i] << " books\n";
    }

    for (int i = 0; i < members; ++i)
        delete[] borrowedBooks[i];
    delete[] borrowedBooks;
    delete[] bookCounts;

    return 0;
}
