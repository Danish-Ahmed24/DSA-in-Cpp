#include<iostream>
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

    int hashFunction(int key) {
        return key % tableSize;
    }

    float loadFactor() {
        return (float)numKeys / tableSize;
    }

    void rehash() {
        int oldSize = tableSize;
        tableSize *= 2; // double the table size
        Entry** oldTable = table;

        table = new Entry*[tableSize];
        for(int i = 0; i < tableSize; i++)
            table[i] = new Entry();
        
        numKeys = 0; // will re-insert keys

        // Re-insert old keys
        for(int i = 0; i < oldSize; i++) {
            if(oldTable[i]->isOccupied && !oldTable[i]->isDeleted) {
                insert(oldTable[i]->key);  // insert in new table
            }
            delete oldTable[i];
        }
        delete[] oldTable;
    }

    void insert(int key) {
        if(loadFactor() > 0.7)
            rehash();

        int index = hashFunction(key);
        int startIndex = index;

        while(table[index]->isOccupied && !table[index]->isDeleted) {
            index = (index + 1) % tableSize;
            if(index == startIndex) {
                cout << "Table Full\n";
                return;
            }
        }

        table[index]->key = key;
        table[index]->isOccupied = true;
        table[index]->isDeleted = false;
        numKeys++;
    }

    bool search(int key) {
        int index = hashFunction(key);
        int startIndex = index;

        while(table[index]->isOccupied || table[index]->isDeleted) {
            if(table[index]->isOccupied && !table[index]->isDeleted && table[index]->key == key)
                return true;

            index = (index + 1) % tableSize;
            if(index == startIndex)
                break;
        }
        return false;
    }

    void remove(int key) {
        int index = hashFunction(key);
        int startIndex = index;

        while(table[index]->isOccupied || table[index]->isDeleted) {
            if(table[index]->isOccupied && !table[index]->isDeleted && table[index]->key == key) {
                table[index]->isDeleted = true;
                table[index]->isOccupied = false;
                numKeys--;
                return;
            }

            index = (index + 1) % tableSize;
            if(index == startIndex)
                break;
        }
        cout << "Key not found\n";
    }
};

int main() {
    HashTable ht;

    ht.insert(7);
    ht.insert(12);
    ht.insert(17);
    ht.insert(22); // triggers rehash

    cout << ht.search(12) << endl; // 1
    cout << ht.search(99) << endl; // 0

    ht.remove(12);
    cout << ht.search(12) << endl; // 0
}
