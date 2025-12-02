#include<iostream>
#include<queue>
 using namespace std;

class Node{
    public:
    int data;
    Node* left;
    Node* right;

    Node(int val){
        this->data=val;
        left=nullptr;
        right=nullptr;
    }
};

class Bst{
    public:
    Node* root;

    Bst(){root=NULL;}


    Node* insert(Node* root,int val){
        if(root==NULL){
            return new Node(val);
        }

        if(val<root->data){
            root->left=insert(root->left,val);
        }
        else{
            root->right=insert(root->right,val);
        }
        return root;
    }

    void insert(int val){
        root = insert(root,val);
    }


    void preorder(Node* root){
        if(root==NULL){
            return;
        }

        cout<<root->data<<" ";
        preorder(root->left);
        preorder(root->right);
    }

    void inorder(Node* root){
        if(root==NULL){
            return;
        }

        inorder(root->left);
        cout<<root->data<<" ";
        inorder(root->right);
    }

    void levelOrder(Node* root){
        if(root==NULL){
            return;
        }
        
        queue<Node*> q;
        q.push(root);
        
        while (!q.empty())
        {
            Node* curr = q.front();
            q.pop();
            cout<<curr->data<<" ";
            if(curr->left)
                q.push(curr->left);
            if(curr->right)
                q.push(curr->right);
        }
        

    }
 
    void postorder(Node* root){
        if(root == NULL){
            return;
        }

        postorder(root->left);
        postorder(root->right);
        cout<<root->data<<" ";
    }



    Node* search(Node* root,int val){
        if(root==NULL || root->data==val){
            return root;
        }else if (val<root->data){
            return search(root->left,val);
        }else{
            return search(root->right,val);
        }
    }

    Node* findMin(Node* root){
        if(root== NULL || root->left==NULL){
            return root;
        }
        return findMin(root->left);

    }
    Node* deleteNode(Node* root,int data){
        if(root == NULL){
            return root;
        }

        if(data<root->data){
            root->left=deleteNode(root->left,data);
        }
        else if(data>root->data){
            root->right=deleteNode(root->right,data);
        }
        else{
            if(root->left == NULL){
                Node* temp = root->right;
                delete(root);
                return temp;
            }
            if(root->right==NULL){
                Node* temp = root->left;
                delete(root);
                return temp;
            }

            Node* min = findMin(root->right);
            root->data=min->data;
            root->right=deleteNode(root->right,min->data);
        }
        return root;
    }
};


int main()
{
    Bst bst;
    bst.insert(1);
    bst.insert(2);
    bst.insert(3);
    bst.insert(4);
    bst.insert(5);
    bst.insert(6);
    bst.insert(7);

    bst.preorder(bst.root);
}