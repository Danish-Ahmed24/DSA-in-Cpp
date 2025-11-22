#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    int height;
    int size;

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
        height = 1;
        size = 1;
    }
};

class AVLTree {
private:
    Node* root;

    int getHeight(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    int getSize(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->size;
    }

    int getBalance(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    void updateNode(Node* node) {
        if (node == nullptr) {
            return;
        }
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        node->size = 1 + getSize(node->left) + getSize(node->right);
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateNode(y);
        updateNode(x);

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateNode(x);
        updateNode(y);

        return y;
    }

    Node* insertNode(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }

        if (value < node->data) {
            node->left = insertNode(node->left, value);
        } else if (value > node->data) {
            node->right = insertNode(node->right, value);
        } else {
            return node;
        }

        updateNode(node);

        int balance = getBalance(node);

        if (balance > 1 && value < node->left->data) {
            return rotateRight(node);
        }

        if (balance < -1 && value > node->right->data) {
            return rotateLeft(node);
        }

        if (balance > 1 && value > node->left->data) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && value < node->right->data) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node* getMinNode(Node* node) {
        Node* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    Node* deleteNode(Node* node, int value) {
        if (node == nullptr) {
            return node;
        }

        if (value < node->data) {
            node->left = deleteNode(node->left, value);
        } else if (value > node->data) {
            node->right = deleteNode(node->right, value);
        } else {
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp = node->left ? node->left : node->right;

                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                Node* temp = getMinNode(node->right);
                node->data = temp->data;
                node->right = deleteNode(node->right, temp->data);
            }
        }

        if (node == nullptr) {
            return node;
        }

        updateNode(node);

        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0) {
            return rotateRight(node);
        }

        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && getBalance(node->right) <= 0) {
            return rotateLeft(node);
        }

        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    int countGreater(Node* node, int value) {
        if (node == nullptr) {
            return 0;
        }

        if (node->data <= value) {
            return countGreater(node->right, value);
        } else {
            return 1 + getSize(node->right) + countGreater(node->left, value);
        }
    }

    void inorderTraversal(Node* node) {
        if (node == nullptr) {
            return;
        }
        inorderTraversal(node->left);
        cout << node->data << " ";
        inorderTraversal(node->right);
    }

public:
    AVLTree() {
        root = nullptr;
    }

    void insert(int value) {
        root = insertNode(root, value);
    }

    void remove(int value) {
        root = deleteNode(root, value);
    }

    int countGreaterThan(int value) {
        return countGreater(root, value);
    }

    void display() {
        inorderTraversal(root);
        cout << endl;
    }
};

int main() {
    AVLTree tree;

    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    cout << "AVL Tree (Inorder): ";
    tree.display();

    cout << "Count greater than 50: " << tree.countGreaterThan(50) << endl;
    cout << "Count greater than 30: " << tree.countGreaterThan(30) << endl;
    cout << "Count greater than 65: " << tree.countGreaterThan(65) << endl;

    tree.remove(70);
    cout << "\nAfter removing 70:" << endl;
    cout << "AVL Tree (Inorder): ";
    tree.display();
    cout << "Count greater than 50: " << tree.countGreaterThan(50) << endl;

    return 0;
}