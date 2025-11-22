    #include<iostream>
    using namespace std;
    int moves = 0;
    int fixMoves =0;
    class Node{
        public:
            int data;
            Node* next;

            Node(int val){
                data=val;
                next=NULL;
            }
    };

    class Stack{
        public:
            Node* top;

        Stack(){
            top=NULL;
        }
        bool isEmpty(){return top==NULL;}
        
        void push(int data){
                Node* newnode = new Node(data);
                newnode->next=top;
                top=newnode;
        }

        int pop(){
            if(!isEmpty()){
                int p = top->data;
                top = top->next;
                return p;
            }
            cout<<"POP";
            return -1;
        }    

        
    };
    void printStack(string name, Stack s) {
        cout << name << ": ";
        Node* temp = s.top;
        while(temp != NULL) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    void bigMove(Stack& S, Stack &D){
        Stack TEMP = Stack();
        while(!S.isEmpty()){
            TEMP.push(S.pop());
        }
        while(!TEMP.isEmpty()){
            D.push(TEMP.pop());
        }
    }
    void towerOfHanoi(int n,Stack &S,Stack &H,Stack &D,int k){
        if(n==0||moves==k){
            return;
        }
        towerOfHanoi(n-1,S,D,H,k);
        if(moves==k) return;
        D.push(S.pop());
        moves++;
        towerOfHanoi(n-1,H,S,D,k);
        return;
    }
//     void fixTower(Stack &D, Stack &H, Stack &S) {
//     // Step 1: Count total disks
//     int total = 0;
//     Stack temp = D;
//     while (!temp.isEmpty()) {
//         total++;
//         temp.pop();
//     }

//     // Step 2: Separate correct top part (smallest disks)
//     Stack Correct, Wrong;
//     int expected = 1;
//     while (!D.isEmpty()) {
//         int val = D.pop();
//         if (val == expected) {
//             Correct.push(val);
//             expected++;
//         } else {
//             Wrong.push(val);
//         }
//     }

//     if (Wrong.isEmpty()) return; // already fixed

//     int wrongCount = 0;
//     Stack countTemp = Wrong;
//     while (!countTemp.isEmpty()) { wrongCount++; countTemp.pop(); }

//     // Step 3: Move Wrong part legally to rebuild
//     int before = moves;
//     towerOfHanoi(wrongCount, Wrong, S, H, 1000);
//     towerOfHanoi(wrongCount, H, S, D, 1000);
//     fixMoves = moves - before;

//     // Step 4: Put back Correct top disks
//     while (!Correct.isEmpty()) {
//         D.push(Correct.pop());
//     }
// }





    int main(){
        Stack S = Stack();
        S.push(5);
        S.push(4);
        S.push(3);
        S.push(2);
        S.push(1);
        Stack H = Stack();
        Stack D = Stack();
        int k = 2;
        int n = 5;
        printStack("Source",S);printStack("Helper",H);printStack("Destination",D);cout<<"--------------------------------"<<endl;

        //before big move
        towerOfHanoi(n,S,H,D,k);
        printStack("Source",S);printStack("Helper",H);printStack("Destination",D);cout<<"--------------------------------"<<endl;
        
        //big move
        bigMove(S,D);
        printStack("Source",S);printStack("Helper",H);printStack("Destination",D);cout<<"--------------------------------"<<endl;
        
        //after big move
        // fixTower(D, H, S);
        // printStack("Source",S);printStack("Helper",H);printStack("Destination",D);cout<<"--------------------------------"<<endl;
        // cout<<"Steps: "<<fixMoves;

        
        cout<<"Steps: "<<moves ;
        return 0;
    }