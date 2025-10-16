#include<iostream>
using namespace std;

class Node{
    public:
    int data;
    Node* next;
    Node(int data){
        this->data=data;
        next=NULL;
    }

};

class Circular{
    public:
    Node *head ,*tail;

    bool headNull(int data){
        Node* newnode = new Node(data);
        if(head==NULL){
            head=newnode;
            tail=newnode;
            tail->next=head;
            return true;
        }
        return false;
    }

    void insertAtEnd(int data){
        if(headNull(data)) return;

        Node* newnode = new Node(data);
        tail->next=newnode;
        newnode->next=head;
        tail = newnode;
    }
    void del(int data)
    {
        if(head == NULL) return ;
        if(head->data==data){
            Node * a = head;
            head = head->next;
            tail->next = head;
            delete a;
            return ;
        }
        Node* curr = head->next;
        Node* prev = head;
        do{
            if(curr->data==data){
                prev->next=curr->next;
              
                delete curr;
                break;
            }
            prev = curr;
            curr=curr->next;
        }while(curr!=head);
    }
    void display(){
        Node* t = head;
        do{
            cout<<t->data<<" ";
            t=t->next;
        }while(t!=head);
        cout<<endl;
    }
};
int main(){
    Circular c = Circular();
    c.insertAtEnd(1);
    c.insertAtEnd(2);
    c.insertAtEnd(3);
    c.insertAtEnd(4);
    c.insertAtEnd(5);
    c.display();
    c.del(3);
    c.display();
    return 0;
}