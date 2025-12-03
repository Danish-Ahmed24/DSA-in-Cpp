#include<iostream>
using namespace std;

class Entry {
public:
    int key;
    string value;
    bool isOccupied;
    bool isDeleted;

    Entry() {
        isOccupied = false;
        isDeleted = false;
    }
};

const int tableSize = 10;
class HashTable{
    public:
        Entry* table[tableSize];

        HashTable(){
            for(int i =0 ; i < tableSize ; i++){
                table[i]=nullptr;
            }
        }

        void insert(int key , string value){
            int index =hashFunction(key);
            
            int startIndex = index;

            while(table[index]!=nullptr && table[index]->isOccupied && table[index]->key!=key){
                index = (index+1)%tableSize;
                if(index == startIndex){
                    cout<<"full";
                    return;
                }
            }

            if(table[index] == nullptr){
                table[index] = new Entry();
            }

            table[index]->value=value;
            table[index]->key=key;
            table[index]->isOccupied=true;
            table[index]->isDeleted=false;
            
        }

        string search(int key){
            int index = hashFunction(key);
            int startIndex = index;

           while(table[index]!=nullptr){
                if(table[index]->isOccupied && !table[index]->isDeleted && table[index]->key==key){
                    return table[index]->value;
                }

                index = (index +1)%tableSize;
                if(index == startIndex){
                    break;
                }  
           }

           return "NOT found";

        }

        void remove(int key){
            int index = hashFunction(key);
            int startIndex = index;

            while(table[index]!=nullptr){
                
                if(table[index]->isOccupied && !table[index]->isDeleted && table[index]->key==key){
                    table[index]->isDeleted=true;
                    table[index]->isOccupied=false;
                    return;
                }

                index = (index+1)%tableSize;
            }
            cout<<"Not found";
        }

        int hashFunction(int key){
            return key%tableSize;
        }
};

int main()
{
    
}