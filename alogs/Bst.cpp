#include<iostream>
#include <queue>
#include <iomanip>
using namespace std;



class Node {
    public:
    int data;
    Node* left;
    Node* right;

    Node(int data){
        this->data=data;
        this->left=NULL;
        this->right=NULL;
    }
};
void inorder(Node* root){
    if(!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}
Node* min(Node* root);
Node* maxi(Node* root);


Node* search(Node* root,int data){
    if(root==NULL){
        return NULL;
    }
    if(root->data==data){
        return root;
    }else if (data<root->data){
        return search(root->left,data);
    }else if (data>root->data){
        return search(root->right,data);
    }
    return nullptr;

}

void preorder(Node* root){
    if(!root) return;
    cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root){
    if(!root) return;
    postorder(root->left);
    postorder(root->right);
    cout<<root->data<<" ";
}
Node* del(Node* root, int data) {
    if (root == NULL) return NULL;

    if (data < root->data) {
        root->left = del(root->left, data);
    }
    else if (data > root->data) {
        root->right = del(root->right, data);
    }
    else {
        // Case 1: No child
        if (root->left == NULL && root->right == NULL) {
            delete root;
            return NULL;
        }
        // Case 2: Only right child
        else if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        // Case 3: Only left child
        else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        // Case 4: Two children
        else {
            Node* temp = min(root->right);
            root->data = temp->data;
            root->right = del(root->right, temp->data);
        }
    }
    return root;
}


Node* min(Node* root){
    if(root==nullptr){
        return NULL;
    }

    if(root->left==NULL){
        return root;
    }
    else{
        return min(root->left);
    }
}

Node* maxi(Node* root){
    if(root==nullptr){
        return nullptr;
    }
    if(root->right==NULL){
        return root;
    }
    else{
        return maxi(root->right);
    }
}

Node* successor(Node* root){
    if(root==nullptr){
        return nullptr;
    }
    if(root->right!=nullptr){
        return min(root->right);
    }
    return nullptr;

}
Node* predecessor(Node* root){
    if(root==nullptr){
        return nullptr;
    }

    if(root->left!=nullptr){
        return maxi(root->left);
    }
    return nullptr;
}
void printTree(Node* root, int space = 0, int height = 10) {
    if (root == NULL) return;

    space += height;

    printTree(root->right, space);

    cout << endl;
    for (int i = height; i < space; i++)
        cout << " ";
    cout << root->data << "\n";

    printTree(root->left, space);
}
int heightNodes(Node* root){

    if(root==NULL){
        return 0;
    }

    int leftHeight = heightNodes(root->left);
    int rightHeight = heightNodes(root->right);

    return max(leftHeight,rightHeight)+1;
}

int heightEdges(Node* root){

    if(root == NULL){
        return -1;
    }
    int leftHeight = heightEdges(root->left);
    int righttHeight = heightEdges(root->right);
    return max(leftHeight,righttHeight)+1;
}
Node* insert(Node* root,int data){
        if(root == NULL){
            return new Node(data);
        }
        if(data<root->data){
            root->left=insert(root->left,data);
        }
        else if(data>root->data){
            root->right=insert(root->right,data);
        }

        return root;
    }

int countNodes(Node* root){
    if(root==nullptr)return 0;

    int leftC = countNodes(root->left);
    int rightC = countNodes(root->right);

    return leftC+rightC+1;
}
int main()
{
    int arr[] = {2,4,3,6,2,0};
    Node* root = nullptr;
    for (int i = 0; i < 6; i++)
    {
        root = insert(root,arr[i]);
    }
    cout << "\n\nTree Structure:\n";
printTree(root);


}