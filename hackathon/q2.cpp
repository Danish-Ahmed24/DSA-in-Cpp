#include<iostream>
#include<stack>
using namespace std;

class Node{
    public:
        int data;
        Node* left;
        Node* right;

    Node(int val){
        this->data=val;
    }
};

class Bst{
    public:
        Node* root;

    Bst(){}


    Node* insert(Node* root,int val){
        if(root==NULL){
            return new Node(val);
        }

        if(val<root->data){
            root->left=insert(root->left,val);
        }
        else if(val>root->data){
            root->right=insert(root->right,val);
        }

        return root;
    }

    void insert(int val){
        root = insert(root,val);
    }

    void findPaths(Node* root,int target_sum,int calSum){
        if(root==NULL){
            return;
        }
        if(target_sum==calSum){
            print()
        }
        findPaths(root->left,target_sum,calSum+root->data);

    }
};


int main(){

    return 0;
}