#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of items purchased: ";
    cin >> n;

    double* prices = new double[n];

    cout << "Enter the price of each item:\n";
    for (int i = 0; i < n; ++i) {
        cin >> prices[i];
    }

    double total = 0;
    for (int i = 0; i < n; ++i) {
        total += prices[i];
    }

    double tax = total * 0.05;
    double finalAmount = total + tax;

    cout << "Total before tax: " << total << endl;
    cout << "Tax (5%): " << tax << endl;
    cout << "Final amount to be paid: " << finalAmount << endl;

    delete[] prices;
    return 0;
}
