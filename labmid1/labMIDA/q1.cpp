#include<iostream>
using namespace std;

class Node{
    public:
    int data;
    Node *next;
    Node *prev;

    Node(int data){
        this->data=data;
        next = NULL;
        prev = NULL;
    }
};

class Number{
    public: 
    Node *head,*tail;
    int length;

    Number(){
        head=NULL;
        tail=NULL;
        length=0;
    }
    Number sum(Number n1,Number n2,int carry = 0){
        Number res = Number();
        Node* tail1 = n1.tail;
        Node* tail2 = n2.tail;

        if(n1.head==NULL && n2.head!=NULL){
            return n2;
        }else if(n1.head!=NULL && n2.head==NULL){
            return n1;
        } else if(n1.head == NULL && n2.head==NULL){
            return res;
        } else {
            int i = n1.length,j=n2.length;
            while(i<=n1.length || j<=n2.length){

                if(n1.at(i)->data+n2.at(j)->data +carry > 9){
                    carry = (n1.at(i)->data+n2.at(j)->data +carry)%100;
                    res.insert(9);
                }
                else{
                    res.insert(n1.at(i)->data+n2.at(j)->data+carry);
                    carry=0;
                }
                i--;
                j--;
            }
        }

        return res;
    }

    Node* at(int index){
        if(index == 0){
            return head;
        }

        Node* temp = head;
        int i = 0;
        while(temp!=NULL){
            if(i==index){
                return temp;
            }
            temp=temp->next;
        }
        return NULL;
    }
    void insert(int data){
        Node* newnode = new Node(data);
        this->length++;
        if(head==NULL){
            head = newnode;
            tail=newnode;
            return;
        }
        newnode->next=head;
        head->prev=newnode;
        head=newnode; 

    }
    void display(){
        Node* temp = head;
        while(temp!=NULL){
            cout<<temp->data<<" -> ";
            temp=temp->next;
        }
        cout<<" ?    LEN("<<this->length<<")"<<endl;
    }
};

int main()
{



    Number n1 = Number();
    n1.insert(1);
    n1.insert(2);
    n1.insert(3);
    n1.insert(4);
    n1.insert(5);
    n1.display();
    Number n2 = Number();
    n2.insert(1);
    n2.insert(5);
    n2.insert(6);
    n2.insert(7);
    n2.insert(8);
    n2.display();

    Number sum1 = Number();
    sum1 = sum1.sum(n1,n2);
    sum1.display();
    return 0;
}