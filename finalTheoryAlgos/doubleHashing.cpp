#include <iostream>
using namespace std;

class Entry {
public:
    int key;
    bool isOccupied;
    bool isDeleted;

    Entry() {
        key = -1;
        isOccupied = false;
        isDeleted = false;
    }
};

class HashTable {
public:
    Entry** table;
    int tableSize;
    int numKeys;

    HashTable(int size = 5) {
        tableSize = size;
        table = new Entry*[tableSize];
        for(int i = 0; i < tableSize; i++)
            table[i] = new Entry();
        numKeys = 0;
    }

    int h1(int key) {
        return key % tableSize;
    }

    int h2(int key) {
        int R = tableSize - 2; // prime smaller than tableSize
        return R - (key % R);
    }

    float loadFactor() {
        return (float)numKeys / tableSize;
    }

    void rehash() {
        int oldSize = tableSize;
        tableSize *= 2;
        Entry** oldTable = table;

        table = new Entry*[tableSize];
        for(int i = 0; i < tableSize; i++)
            table[i] = new Entry();

        numKeys = 0;

        for(int i = 0; i < oldSize; i++) {
            if(oldTable[i]->isOccupied && !oldTable[i]->isDeleted)
                insert(oldTable[i]->key);
            delete oldTable[i];
        }
        delete[] oldTable;
    }

    void insert(int key) {
        if(loadFactor() > 0.7)
            rehash();

        int index = h1(key);
        int step = h2(key);
        int i = 0;
        int newIndex;

        while(true) {
            newIndex = (index + i * step) % tableSize;

            if(!table[newIndex]->isOccupied || table[newIndex]->isDeleted) {
                table[newIndex]->key = key;
                table[newIndex]->isOccupied = true;
                table[newIndex]->isDeleted = false;
                numKeys++;
                return;
            }

            i++;
            if(i == tableSize) {
                cout << "Table Full\n";
                return;
            }
        }
    }

    bool search(int key) {
        int index = h1(key);
        int step = h2(key);
        int i = 0;
        int newIndex;

        while(i < tableSize) {
            newIndex = (index + i * step) % tableSize;

            if(table[newIndex]->isOccupied && !table[newIndex]->isDeleted && table[newIndex]->key == key)
                return true;

            if(!table[newIndex]->isOccupied && !table[newIndex]->isDeleted)
                return false;

            i++;
        }
        return false;
    }

    void remove(int key) {
        int index = h1(key);
        int step = h2(key);
        int i = 0;
        int newIndex;

        while(i < tableSize) {
            newIndex = (index + i * step) % tableSize;

            if(table[newIndex]->isOccupied && !table[newIndex]->isDeleted && table[newIndex]->key == key) {
                table[newIndex]->isDeleted = true;
                table[newIndex]->isOccupied = false;
                numKeys--;
                return;
            }

            if(!table[newIndex]->isOccupied && !table[newIndex]->isDeleted)
                break;

            i++;
        }
        cout << "Key not found\n";
    }
};

int main() {
    HashTable ht;

    ht.insert(10);
    ht.insert(24);
    ht.insert(31);
    ht.insert(45); // may trigger rehash

    cout << ht.search(24) << endl; // 1
    cout << ht.search(99) << endl; // 0

    ht.remove(24);
    cout << ht.search(24) << endl; // 0
}
