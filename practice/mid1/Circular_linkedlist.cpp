#include<iostream>

using namespace std;

class node{
 public:
	int data;
	node* next;
	
	node(){
		data=0; 
		next=NULL;
	}
	node(int value){
		data=value;
		next=NULL;
	}
};

class Clinkedlist{
	public:
	node *head,*tail;
	
	Clinkedlist(){
		head=NULL;
		tail=NULL;
	}
	
	// Insert operation
	void insertAtEnd(int data){
		node *newnode= new node(data);
		
		if(head==NULL && tail==NULL){
			head=newnode;
			tail=newnode;
			tail->next=head;
		}
		else{
			tail->next=newnode;
			tail=newnode;
			tail->next=head;
		}
	}
	
	void insertAtFront(int data){
		node *newnode= new node(data);
		newnode->next=head;
		head=newnode;
		tail->next=head;
	}
	
	//if the position is head or tail, you have to explicitly write a condition.
	void insertafterPosition(int data, int pos){
		node *newnode=new node(data);
		node *prev=head;
		node *curr=head;
		for(int i=0;i <pos;i++){
			curr=prev;
			prev=prev->next;
		}
		curr->next=newnode;
		newnode->next=prev;
	}
	void insertatPosition(int data, int pos){
		node *newnode=new node(data);
		node *prev=head;
		node *curr=head;
		for(int i=1;i <pos;i++){
			curr=prev;
			prev=prev->next;
		}
		curr->next=newnode;
		newnode->next=prev;
	}
    
    void insertafterdata(int data, int existingdata){
    	node *newnode= new node(data);
    	node *curr=head;
    	node *prev=head;
    	while(curr->next!=NULL && curr->data!=existingdata){
    		curr=prev;
    		prev=prev->next;
		}
		curr->next=newnode;
		newnode->next=prev;
	}
	
	//delete operation
	void deleteatfront(){
		node *temp=head;
		head=head->next;
		tail->next=head;
		delete temp;
	}
	
	void deleteatend(){
		node *temp=head;
		while(temp->next!=tail){
			temp=temp->next;
		}
		delete tail;
		tail=temp;
		tail->next=head;
	}
	
	//only if the value is not the head node neither the tail node, you have to write specific conditions for both head and tail
	void deletebyvalue(int value){
		node *curr=head;
		node *prev=head;
		while(curr->next!=NULL && curr->data!=value ){
			prev=curr;
			curr=curr->next;
		}
		prev->next=curr->next;
		delete curr;
	}
	
	void deleteafterposition(int pos){
		node *curr=head;
		node *prev=head;
		for(int i=0; i<pos;i++){
			prev=curr;
			curr=curr->next;
		}
		prev->next=curr->next;
		delete curr;
	}
	
//concatenate the two lists
   void concatenate(Clinkedlist &otherlinkedlist){
   	//if the other linkedlist is empty
   	if(otherlinkedlist.head==NULL){
   		return;
	   }
	   //if current list is empty
	   if(head==NULL){
	   	head=otherlinkedlist.head;
	   	tail=otherlinkedlist.tail;
	   	tail->next=head;
	   }
	   else{
	   	tail->next=otherlinkedlist.head;
	   	tail=otherlinkedlist.tail;
	   	tail->next=head;
	   }
	   
	   otherlinkedlist.head=NULL;
	   otherlinkedlist.tail=NULL;
   }	
	
	
// searching in linked list	
	bool search(int data){
		node *temp=head;
		do{
			if(temp->data==data){
				return true;
			}
			else{
				temp=temp->next;
			}
			
		}while(temp!=head);
		return false;
	}
	
//display elements in the linked list
	void display(){
		node *temp=head;
		if(head==NULL){
			cout <<"linked list is empty" << endl;
			return;
		}
		do{
			cout << temp->data << endl;
			temp=temp->next;	
		}
		while(temp!=head);
	}
};


int main(){
//	Clinkedlist ll;
//	ll.insertAtEnd(34);
//	ll.insertAtEnd(56);
//	ll.insertAtFront(67);
//	ll.insertAtEnd(78);
//	ll.insertAtEnd(780);
//	ll.insertafterdata(100,56);
//	ll.insertafterPosition(1,2);
//	ll.insertatPosition(4,2);
//	ll.insertPosition(9,2);
//	ll.display();
//	cout << (ll.search(86) ? "Found" : "Not Found") << endl;
//	ll.deleteatfront();
//	ll.display();
//	ll.deleteatend();
//	ll.display();
//	ll.deletebyvalue(78);
//	ll.display();
//	ll.deleteafterposition(3);
//	ll.display();
Clinkedlist l1, l2;
   l1.insertAtEnd(1);
    l1.insertAtEnd(2);
    l1.insertAtEnd(3);

	l2.insertAtEnd(4);
    l2.insertAtEnd(5);
    l2.insertAtEnd(6);

    cout << "List 1 before concat:\n";
    l1.display();
    cout << "List 2 before concat:\n";
    l2.display();

    l1.concatenate(l2);

    cout << "After concatenation (l1):\n";
    l1.display();

    cout << "List 2 after concat:\n";
    l2.display(); // will be empty if we "moved" nodes
}
