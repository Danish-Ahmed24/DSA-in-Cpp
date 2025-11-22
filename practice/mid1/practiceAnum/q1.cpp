#include<iostream>

using namespace std;

// START: linklist code
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

class linkedlist{
 public:
	node *head,*tail;
	
	linkedlist(){
		head=NULL;
		tail=NULL;
	}
	
	// Insert operation
	//done
	void insertAtEnd(int data){
		node *newnode= new node(data);
		
		if(head==NULL && tail==NULL){
			head=newnode;
			tail=newnode;
		}
		else{
			tail->next=newnode;
			tail=newnode;
		}
	}
	//done
	void insertAtFront(int data){
		node *newnode= new node(data);
		newnode->next=head;
		head=newnode;
	}
	//done
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
	//done
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
    //done
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
	//done	
	void deleteatfront(){
		node *temp=head;
		head=head->next;
		delete temp;
	}
	//done
	void deleteatend(){
		node *temp=head;
		while(temp->next!=tail){
			temp=temp->next;
		}
		delete tail;
		tail=temp;
		tail->next=NULL;
	}
	
	//only if the value is not the head node neither the tail node, you have to write specific conditions for both head and tail
	//done
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
	//done
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
	//done
   void concatenate(linkedlist &otherlinkedlist){
   	//if the other linkedlist is empty
   	if(otherlinkedlist.head==NULL){
   		return;
	   }
	   //if current list is empty
	   if(head==NULL){
	   	head=otherlinkedlist.head;
	   	tail=otherlinkedlist.tail;
	   }
	   else{
	   	tail->next=otherlinkedlist.head;
	   	tail=otherlinkedlist.tail;
	   }
	   
	   otherlinkedlist.head=NULL;
	   otherlinkedlist.tail=NULL;
   }	
	
	
// searching in linked list	
	bool search(int data){
		node *temp=head;
		while(temp->next!=NULL){
			if(temp->data==data){
				return true;
			}
			temp=temp->next;
		}
		return false;
	}
	
//display elements in the linked list
	void display(){
		node *temp=head;
		if(head==NULL){
			cout <<"linked list is empty" << endl;
			return;
		}
		
		while(temp!=NULL){
			cout << temp->data << endl;
			temp=temp->next;
		}
	}
};
// END: linklist code

//ALGO here 
bool is_cycleList(node *head){
    if(head ==NULL || head->next == NULL){
        return false;
    }

    node* slow = head;
    node* fast = head;
    
    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;

        if(slow == fast)
        {
            return true;
        }
    }

    return false;
}