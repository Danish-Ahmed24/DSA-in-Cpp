#include <iostream>
using namespace std;

class Node {
public:
    char word[10];
    int count;
    Node* next;
    Node(const char w[]) {
        int i = 0;
        while (w[i] != '\0') {
            word[i] = w[i];
            i++;
        }
        word[i] = '\0';
        count = 1;
        next = 0;
    }
};

int myStrCmp(const char a[], const char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] < b[i]) return -1;
        if (a[i] > b[i]) return 1;
        i++;
    }
    if (a[i] == '\0' && b[i] == '\0') return 0;
    if (a[i] == '\0') return -1;
    return 1;
}

int hashFunction(const char w[]) {
    int i = 0;
    int h = 0;
    while (w[i] != '\0') {
        h = h * 31 + (int)w[i];
        i++;
    }
    if (h < 0) h = -h;
    return h % 20;
}

void insertOrUpdate(Node* table[], const char w[]) {
    int index = hashFunction(w);
    Node* head = table[index];
    Node* temp = head;
    while (temp != 0) {
        if (myStrCmp(temp->word, w) == 0) {
            temp->count = temp->count + 1;
            return;
        }
        temp = temp->next;
    }
    Node* n = new Node(w);
    n->next = table[index];
    table[index] = n;
}

int main() {
    const int TABLE_SIZE = 20;
    Node* table[TABLE_SIZE];
    int i = 0;
    while (i < TABLE_SIZE) {
        table[i] = 0;
        i++;
    }

    const char w1[] = "the";
    const char w2[] = "cat";
    const char w3[] = "and";
    const char w4[] = "the";
    const char w5[] = "dog";
    const char w6[] = "and";
    const char w7[] = "the";
    const char w8[] = "mouse";

    insertOrUpdate(table, w1);
    insertOrUpdate(table, w2);
    insertOrUpdate(table, w3);
    insertOrUpdate(table, w4);
    insertOrUpdate(table, w5);
    insertOrUpdate(table, w6);
    insertOrUpdate(table, w7);
    insertOrUpdate(table, w8);

    cout << "Hash table (index: word(count) ...):" << endl;
    i = 0;
    while (i < TABLE_SIZE) {
        cout << "Index " << i << ":";
        Node* temp = table[i];
        if (temp == 0) {
            cout << " empty";
        } else {
            while (temp != 0) {
                cout << " " << temp->word << "(" << temp->count << ")";
                temp = temp->next;
            }
        }
        cout << endl;
        i++;
    }

    char maxWord[10];
    int maxCount = 0;
    int j;
    i = 0;
    while (i < TABLE_SIZE) {
        Node* temp = table[i];
        while (temp != 0) {
            if (temp->count > maxCount) {
                maxCount = temp->count;
                j = 0;
                while (temp->word[j] != '\0') {
                    maxWord[j] = temp->word[j];
                    j++;
                }
                maxWord[j] = '\0';
            }
            temp = temp->next;
        }
        i++;
    }

    cout << "Most frequent word: " << maxWord << " with count " << maxCount << endl;

    i = 0;
    while (i < TABLE_SIZE) {
        Node* temp = table[i];
        while (temp != 0) {
            Node* del = temp;
            temp = temp->next;
            delete del;
        }
        i++;
    }

    return 0;
}
