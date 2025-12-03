 #include<iostream>
#include<string>
using namespace std;

class Node{
    public:
    int key;
    string value;
    Node* next;

    Node(int k,string v){
        key = k;
        value = v;
        next = NULL;
    }
};
const int tableSize = 10;
class HashTable{
    public:
    Node* table[tableSize];


    HashTable(){
        for(int i =0;i<tableSize;i++){
            table[i]=nullptr;
        }
    }
    void insert(int key , string value){
        int index = hashFunction(key);

        Node* temp = table[index];

        while(temp!=nullptr){
            if(temp->key==key){
                temp->value=value;
                return;
            }
            temp = temp->next;
        }

        Node* newnode = new Node(key , value);
        newnode->next=table[index];
        table[index] = newnode;
        
    }

    string search(int key){
        int index = hashFunction(key);
        Node* temp = table[index];

        while(temp!=nullptr){
            if(temp->key==key){
                return temp->value;
            }

            temp=temp->next;
        }


        return "ERR: 404";

    }
    
    int hashFunction(int key){
        return key%tableSize;
    }

    void remove(int key){
        int index = hashFunction(key);
        Node* temp = table[index];
        Node* prev = nullptr;
        
        if(temp==nullptr){
            cout<<"not found";
            return;
        }

        if(temp->key==key){
            table[index]=temp->next;
            delete temp;
            return;
        }

        while(temp!=nullptr){
            if(temp->key==key){
                prev->next=temp->next;
                delete temp;
                return;
            }
            prev = temp;
            temp = temp->next;
        }

        cout<<"Not found";
        return;
    }
};

int main()
{
    
}