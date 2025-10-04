#include <iostream>
using namespace std;

int population(int n) {

    if (n == 0)
        return 0;
    if (n == 1)
        return 1;

    return population(population(n - 1)) + population(n - 2);
}

int main() {
    int n;
    cout << "Enter year (n): ";
    cin >> n;
    cout << "Population at year " << n << " = " << population(n) << endl;
    return 0;
}
