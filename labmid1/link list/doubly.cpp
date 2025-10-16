#include<iostream>
using namespace std;

class Node{
    public:
    int data;
    Node *next,*prev;

    Node(int data){
        this->data=data;
        next = NULL;
        prev = NULL;
    }
};

class Doubly{
    public:
    Node *head ,*tail;

    void insert_back(int data){
        Node * newnode = new Node(data);
        if(head == NULL){
            head = newnode;
            tail=newnode;
            newnode->prev=NULL;
            return;
        }



        tail->next=newnode;
        newnode->prev=tail;
        tail=newnode;

    }

    void display(bool forward){
        if(forward){
            Node* t = head;
            while(t!=NULL){
                cout<<t->data<<" ";
                t=t->next;
            }
            cout<<endl;
        }
        if(!forward){
            Node* t = tail;
            while(t!=NULL){
                cout<<t->data<<" ";
                t=t->prev;
            }
            cout<<endl;
        }
    }
};
int main(){
    Doubly d = Doubly();
    d.insert_back(1);
    d.insert_back(2);
    d.insert_back(3);
    d.insert_back(4);
    d.display(true);
    d.display(false);
    return 0;
}