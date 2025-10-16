#include<iostream>
using namespace std;

class Node{
    public:
        int data;
        Node *next;

        Node(int data){
            this->data=data;
            next=NULL;
        }
    };

class Singly{
    public:
    Node *head,*tail;
    
    Singly(){
        head = NULL;
        tail = NULL;
    }
    void insert_at(int data,int index){
        //check for index EDGE case if time have
        // <3
        if(index <= 0){
            this->insert_front(data);
            return;
        }
        Node* newnode = new Node(data);
        Node* t = head;
        int i = 0;
        while(i < index){
            t=t->next;
            i++;
        }
        newnode->next=t->next;
        t->next=newnode;
    }   
    void insert_front(int data){
        Node* newnode = new Node(data);
        if(head == NULL){
            head = newnode;
            tail = newnode;
            return;
        }
        newnode->next=head;
        head=newnode;
    }
    void insert_back(int data){
        Node* newnode =new Node(data);
        if(head == NULL){
            head = newnode;
            tail = newnode;
            return;
        }
        
        tail->next = newnode;
        tail = newnode;

    }
    void display(){
        Node *temp = head;
        while(temp != NULL){
            cout<< temp->data <<" ";
            temp=temp->next;
        }
        cout<<endl;
    }
    bool search(int data){
        Node* t = head;
        while(t!=NULL){
            if(t->data==data){
                cout<<"found"<<endl;
                return true;
            }
            t=t->next;
        }
        cout<<"not found"<<endl;
        return false;
    }
    void deleteAtEnd() {
    if (head == NULL) {
        cout << "List is empty!" << endl;
        return;
    }

    // Case 1: only one node
    if (head == tail) {
        delete head;
        head = tail = NULL;
        return;
    }

    // Case 2: multiple nodes — find the 2nd last
    Node* t = head;
    while (t->next != tail) {
        t = t->next;
    }

    delete tail;
    tail = t;
    tail->next = NULL;
}

};


int main(){
    Singly s = Singly();
    s.display();
    s.insert_back(2);
    s.insert_back(3);
    s.insert_back(4);
    s.insert_back(5);
    s.insert_at(33,3);
    // s.insert_front(99);
    // s.insert_front(99);
    s.display();
    s.search(333);
    s.search(3);
    return 0;
}