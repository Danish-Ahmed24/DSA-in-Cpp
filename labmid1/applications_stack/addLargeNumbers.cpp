#include<iostream>
using namespace std;
class Node{
    public:
        int data;
        Node* next;

    Node(int data){
        this->data=data;
        this->next=NULL;
    }
};

class Stack{
    
    public:
    Node* top;
    
    
    Stack(){
        top=NULL;
    }

    bool isEmpty(){
        return (top==NULL);
    }

    void push(int data){
        Node *n = new Node(data);
        n->next=top;
        top = n;
    }
    
    
    int pop() {
    if (isEmpty()) {
        return 0;
    }
    Node *n = top;
    int value = n->data;
    top = top->next;
    delete n;
    return value;
}


    
    void display(){
        Node* n = top;
        while(n!=NULL){
            cout<<n->data<<endl<<"___"<<endl;
            n=n->next;
        }
    }
};

void add(int num1,int num2){
    Stack n1 = Stack();
    Stack n2 = Stack();
    Stack base = Stack();
    Stack res = Stack();
    while(num1>0)
    {
        base.push(num1%10);
        num1/=10;
    }

    while(!base.isEmpty()){
        n1.push(base.pop());
    }

    while(num2>0){
        base.push(num2%10);
        num2/=10;
    }

    while(!base.isEmpty()){
        n2.push(base.pop());
    }
    int carry = 0;
    while(!n1.isEmpty() || !n2.isEmpty() || carry!=0){
        int sum = n1.pop() + n2.pop() +carry;
        res.push(sum%10);
        carry = sum/10;
    
        
    }
    res.display();
}
int main(){
    int num1 = 7891;
    int num2 = 8327;
    add(num1,num2);

    return 0;
}