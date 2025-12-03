#include <iostream>
using namespace std;

// Node class
class Node {
public:
    int data;
    Node* left;
    Node* right;
    int height;

    Node(int val) {
        data = val;
        left = right = nullptr;
        height = 1;
    }
};

// AVL Tree class
class AVL {
public:
    Node* root;

    AVL() {
        root = nullptr;
    }

    int height(Node* n) {
        return n ? n->height : 0;
    }

    int bf(Node* n) {
        return n ? height(n->left) - height(n->right) : 0;
    }

    // Right rotate
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(height(y->left), height(y->right));
        x->height = 1 + max(height(x->left), height(x->right));

        return x;
    }

    // Left rotate
    Node* leftRotate(Node* y) {
        Node* x = y->right;
        Node* T2 = x->left;

        x->left = y;
        y->right = T2;

        y->height = 1 + max(height(y->left), height(y->right));
        x->height = 1 + max(height(x->left), height(x->right));

        return x;
    }

    // Insert node
    Node* insert(Node* root, int val) {
        if (!root) return new Node(val);

        if (val < root->data)
            root->left = insert(root->left, val);
        else if (val > root->data)
            root->right = insert(root->right, val);
        else
            return root; // duplicates not allowed

        root->height = 1 + max(height(root->left), height(root->right));

        int balance = bf(root);

        // LL
        if (balance > 1 && val < root->left->data)
            return rightRotate(root);

        // RR
        if (balance < -1 && val > root->right->data)
            return leftRotate(root);

        // LR
        if (balance > 1 && val > root->left->data) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // RL
        if (balance < -1 && val < root->right->data) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    void insertVal(int val) {
        root = insert(root, val);
    }

    // Minimum value node (used in deletion)
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left)
            current = current->left;
        return current;
    }

    // Delete node
    Node* deleteNode(Node* root, int key) {
        if (!root) return root;

        if (key < root->data)
            root->left = deleteNode(root->left, key);
        else if (key > root->data)
            root->right = deleteNode(root->right, key);
        else {
            // Node found
            if (!root->left || !root->right) {
                Node* temp = root->left ? root->left : root->right;
                if (!temp) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp;
                }
                delete temp;
            } else {
                Node* temp = minValueNode(root->right);
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->data);
            }
        }

        if (!root) return root;

        root->height = 1 + max(height(root->left), height(root->right));
        int balance = bf(root);

        // LL
        if (balance > 1 && bf(root->left) >= 0)
            return rightRotate(root);

        // LR
        if (balance > 1 && bf(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // RR
        if (balance < -1 && bf(root->right) <= 0)
            return leftRotate(root);

        // RL
        if (balance < -1 && bf(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    void deleteVal(int val) {
        root = deleteNode(root, val);
    }

    // Inorder traversal
    void inorder(Node* root) {
        if (!root) return;
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }

    void printInorder() {
        inorder(root);
        cout << endl;
    }
};

// ----------------- MAIN -----------------
int main() {
    AVL tree;

    tree.insertVal(10);
    tree.insertVal(20);
    tree.insertVal(30);
    tree.insertVal(25);
    tree.insertVal(5);

    cout << "Inorder after insertion: ";
    tree.printInorder();

    tree.deleteVal(20);
    cout << "Inorder after deleting 20: ";
    tree.printInorder();

    tree.deleteVal(30);
    cout << "Inorder after deleting 30: ";
    tree.printInorder();

    return 0;
}
