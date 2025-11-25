#include <iostream>
using namespace std;

class Node {
public:
    long long value;
    Node* next;
    Node(long long v) {
        value = v;
        next = 0;
    }
};

int hashFunction(long long number) {
    return (int)((number / 1000) % 20);
}

int main() {
    const int TABLE_SIZE = 20;
    Node* table[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) table[i] = 0;

    long long numbers[5];
    numbers[0] = 9081234567LL;
    numbers[1] = 9089876543LL;
    numbers[2] = 9085551212LL;
    numbers[3] = 7321119988LL;
    numbers[4] = 7325550199LL;

    for (int i = 0; i < 5; i++) {
        long long num = numbers[i];
        int index = hashFunction(num);
        Node* n = new Node(num);
        if (table[index] == 0) {
            table[index] = n;
        } else {
            Node* temp = table[index];
            while (temp->next != 0) temp = temp->next;
            temp->next = n;
        }
    }

    for (int i = 0; i < 5; i++) {
        long long num = numbers[i];
        int index = hashFunction(num);
        cout << "Number " << num << " hashes to index " << index << endl;
    }

    cout << "Final chains:" << endl;
    for (int i = 0; i < TABLE_SIZE; i++) {
        cout << "Index " << i << ":";
        Node* temp = table[i];
        if (temp == 0) {
            cout << " empty";
        } else {
            while (temp != 0) {
                cout << " " << temp->value;
                temp = temp->next;
            }
        }
        cout << endl;
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* temp = table[i];
        while (temp != 0) {
            Node* del = temp;
            temp = temp->next;
            delete del;
        }
    }

    return 0;
}
