// Max heap ki baat hori hai
#include<iostream>

using namespace std;
class Node{
    public:
        int data;
        Node* left;
        Node* right;
    
        Node(int val){
            this->data=val;
            this->left=NULL;
            this->right=NULL;
        }
};

bool isCBT(Node* root,int i,int nodesCount){
    if(i >= nodesCount){
        return false;
    }
    if(root == NULL) return true;   
    
    return isCBT(root->left,i*2 +1,nodesCount) && isCBT(root->right,i*2 +2,nodesCount);
}
//fhidhnfjlgnfngbofrngfnfelgeroignvkmfnboerjgvfngoernvlfnbvfdgoiervfndv fbnergnenfgnfnronrlngnethmflqrpqkpwjmvsmvmdbejwe8tr9fjdturjflknglsmvkjgmvmldnfgfnvfndlnfnknbf.dj;sf;weowiprwvfnb.dkvjgierjgo//
//uyiut1234567890qwertyuiopasdfghjklzxcvbnm]'/[;.=-0987654qaz2wsx3edc4rfv5tgb6yhn7ujm8ik,9ol.0p;]
bool isMaxOrder(Node* root){
    if(root->left==NULL && root->left==NULL)
        return true;
    
    if(root->left!=NULL && root->left->data > root->data)
        return false;
    if(root->left==NULL && root->right->data > root->data)
        return false;
    
    return isMaxOrder(root->left) && isMaxOrder(root->right);
}
int nodesCount(Node* root){
    if(root==NULL){
        return 0;
    }
    return nodesCount(root->left)+nodesCount(root->right)+1;
}

bool solve(Node* root){
    if(root==NULL){
        return true;
    }
    int index = 0;
    int totalNodes = nodesCount(root);
    return isCBT(root,index,totalNodes) && isMaxOrder(root);
}

int main()
{
    
    return 0;
}