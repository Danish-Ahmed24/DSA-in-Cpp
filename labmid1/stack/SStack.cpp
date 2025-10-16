#include<iostream>
using namespace std;

class Stack{
    public:
    static const int STACK_SIZE = 10;
    int stack[STACK_SIZE];
    int top = 0;

    bool isFull(){
        return top==STACK_SIZE;
    }
    bool isEmpty(){
        return top==0;
    }
    
    void push(int data){
        if(isFull()){
            cout<<"ERROR"<<endl;
            return;
        }
        stack[top++]=data;
    }
    void display() {
        if (isEmpty()) {
            cout << "Stack is empty!" << endl;
            return;
        }
        cout << "Stack elements (top → bottom): ";
        for (int i = top - 1; i >= 0; i--) {
            cout << stack[i] << " ";
        }
        cout << endl;
    }
    void pop(){
        if(isEmpty()){
            cout<<"ERROR"<<endl;
            return;
        }
        --top;
    }
};


int main(){
    
    Stack s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.display();
    s.pop();
    s.pop();
    s.display();
    s.push(33);
    s.display();
    return 0;
}


