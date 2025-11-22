#include<iostream>
using namespace std;

class Node{
    public:
    int data;
    Node* next;

    Node(){
        data = 0;
        next =0;
    }
    Node(int data){
        this->data=data;
        next=0;
    }
};

class LinkList{
    public:
    Node* head;
    Node* tail;

    LinkList(){
        head=NULL;
        tail=NULL;
    }

    void insert(int val) {
        Node* newnode = new Node(val);
        if(head==NULL && tail==NULL){
            head = newnode;
            tail=newnode;
        }
        else
        {
            tail->next=newnode;
            tail = newnode;
        }
    }

    void traverse(Node* node){
        if  (node==NULL) return;
        cout<<node->data<<" ";
        return traverse(node->next);
    }

};

int main(){
    LinkList list;
    list.insert(10);
    list.insert(20);
    list.insert(30);

    list.traverse(list.head->next);
    return 0;
}