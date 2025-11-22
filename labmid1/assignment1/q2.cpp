#include <iostream>
#include <stack>
#include <string>
#include <cmath>
using namespace std;

long long movesDone = 0;
long long k_limit = 0;

void hanoi(stack<int> &A, stack<int> &B, stack<int> &C, int n) {
    if (n == 0 || movesDone >= k_limit) return;
    hanoi(A, C, B, n - 1);
    if (movesDone >= k_limit) return;
    if (!A.empty()) {
        C.push(A.top());
        A.pop();
        movesDone++;
    }
    if (movesDone >= k_limit) return;
    hanoi(B, A, C, n - 1);
}

void illegalMove(stack<int> &A, stack<int> &C) {
    stack<int> temp;
    while (!A.empty()) {
        temp.push(A.top());
        A.pop();
    }
    while (!temp.empty()) {
        C.push(temp.top());
        temp.pop();
    }
}

int countLargestFromBottom(stack<int> C, int n) {
    stack<int> temp;
    while (!C.empty()) {
        temp.push(C.top());
        C.pop();
    }
    int expected = n;
    int legal = 0;
    while (!temp.empty()) {
        int val = temp.top();
        temp.pop();
        if (val == expected) {
            legal++;
            expected--;
        } else {
            break;
        }
    }
    return legal;
}

string DecToBin(long long num) {
    if (num == 0) return "0";
    string s = "";
    while (num > 0) {
        s = char('0' + (num % 2)) + s;
        num /= 2;
    }
    return s;
}

int main() {
    int n;
    string k_bin;
    cin >> n >> k_bin;

    long long k = 0;
    for (char c : k_bin)
        k = k * 2 + (c - '0');

    stack<int> A, B, C;
    for (int i = n; i >= 1; i--)
        A.push(i);

    k_limit = k;
    movesDone = 0;
    hanoi(A, B, C, n);

    illegalMove(A, C);

    int legal = countLargestFromBottom(C, n);
    int illegal = n - legal;
    long long remaining = pow(2, illegal) - 1;

    cout << DecToBin(remaining) << "\n";
    return 0;
}
    