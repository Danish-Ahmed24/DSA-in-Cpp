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
    
    
    void pop(){
        if(isEmpty()){
            cout<<"no space";
            return;
        }
        Node *n = top;
        top=top->next;
        delete n;
    }

    
    void display(){
        Node* n = top;
        while(n!=NULL){
            cout<<n->data<<endl<<"___"<<endl;
            n=n->next;
        }
    }
};

int main(){
    Stack st = Stack();
    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);
    st.push(5);

    st.display();
    st.pop();
    st.pop();
    cout<<"                 fffffffffffffffff\n";
    st.display();
    st.pop();
    st.pop();
    st.pop();
    st.pop();
    st.pop();
    st.pop();
    cout<<"                 fffffffffffffffff\n";
    st.display();

    return 0;
}