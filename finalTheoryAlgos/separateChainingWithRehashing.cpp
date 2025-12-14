#include<iostream>
using namespace std;

class Node {
public:
    int key;
    Node* next;

    Node(int k) {
        key = k;
        next = nullptr;
    }
};

class HashTable {
public:
    Node** table;
    int tableSize;
    int numKeys;

    HashTable(int size = 5) {
        tableSize = size;
        table = new Node*[tableSize];
        for(int i = 0; i < tableSize; i++)
            table[i] = nullptr;
        numKeys = 0;
    }

    int hashFunction(int key) {
        return key % tableSize;
    }

    float loadFactor() {
        return (float)numKeys / tableSize;
    }

    void rehash() {
        int oldSize = tableSize;
        tableSize *= 2; // double the size
        Node** oldTable = table;

        table = new Node*[tableSize];
        for(int i = 0; i < tableSize; i++)
            table[i] = nullptr;

        numKeys = 0; // will re-insert keys

        for(int i = 0; i < oldSize; i++) {
            Node* current = oldTable[i];
            while(current != nullptr) {
                insert(current->key);  // re-insert
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] oldTable;
    }

    void insert(int key) {
        if(loadFactor() > 0.7)
            rehash();

        int index = hashFunction(key);
        Node* newNode = new Node(key);
        newNode->next = table[index];
        table[index] = newNode;
        numKeys++;
    }

    bool search(int key) {
        int index = hashFunction(key);
        Node* current = table[index];
        while(current != nullptr) {
            if(current->key == key)
                return true;
            current = current->next;
        } 
        return false;
    }
};

int main() {
    HashTable ht;

    ht.insert(12);
    ht.insert(22);
    ht.insert(32);
    ht.insert(7);   // load factor > 0.7 triggers rehash

    cout << ht.search(22) << endl; // 1
    cout << ht.search(99) << endl; // 0
}
