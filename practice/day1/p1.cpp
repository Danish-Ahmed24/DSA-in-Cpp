#include <iostream>
using namespace std;

class Test {
    int x;
public:
    Test(int val=0) : x(val) {}

    Test& operator=(const Test& other) {  // return by reference, take by const reference
        if (this != &other) {
            x = other.x;
        }
        return *this; // returns reference to current object
    }

    void show() { cout << x << endl; }
};

int main() {
    Test a(10), b(20), c(30);

    a = b = c; // works because return type is reference
    a.show();  // 30
    b.show();  // 30
    c.show();  // 30
}
