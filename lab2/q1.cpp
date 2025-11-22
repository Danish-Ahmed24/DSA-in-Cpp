#include <iostream>
using namespace std;

int main() {
    int students = 5, subjects = 4;
    int** marks = new int*[students];
    for (int i = 0; i < students; ++i)
        marks[i] = new int[subjects];

    for (int i = 0; i < students; ++i) {
        cout << "Enter marks for student " << i + 1 << ":\n";
        for (int j = 0; j < subjects; ++j) {
            cin >> marks[i][j];
        }
    }

    for (int i = 0; i < students; ++i) {
        int sum = 0;
        for (int j = 0; j < subjects; ++j) {
            sum += marks[i][j];
        }
        double average = static_cast<double>(sum) / subjects;
        cout << "Average marks for student " << i + 1 << ": " << average << endl;
    }
    for (int i = 0; i < students; ++i)
        delete[] marks[i];
    delete[] marks;

    return 0;
}
