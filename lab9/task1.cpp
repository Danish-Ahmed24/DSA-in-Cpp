#include <iostream>
using namespace std;

class Book {
public:
    int isbn;
    char title[100];
    bool available;
    
    Book() {
        isbn = 0;
        title[0] = '\0';
        available = true;
    }
    
    Book(int i, const char* t, bool a) {
        isbn = i;
        int j = 0;
        while (t[j] != '\0' && j < 99) {
            title[j] = t[j];
            j++;
        }
        title[j] = '\0';
        available = a;
    }
};

class AVLNode {
public:
    Book book;
    AVLNode* left;
    AVLNode* right;
    int height;
    
    AVLNode() {
        left = nullptr;
        right = nullptr;
        height = 1;
    }
    
    AVLNode(Book b) {
        book = b;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

class AVLTree {
private:
    AVLNode* root;
    
    int getHeight(AVLNode* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }
    
    int getBalance(AVLNode* node) {
        if (node == nullptr) {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }
    
    int max(int a, int b) {
        return (a > b) ? a : b;
    }
    
    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        
        x->right = y;
        y->left = T2;
        
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        
        return x;
    }
    
    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        
        y->left = x;
        x->right = T2;
        
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        
        return y;
    }
    
    AVLNode* insertNode(AVLNode* node, Book book) {
        if (node == nullptr) {
            return new AVLNode(book);
        }
        
        if (book.isbn < node->book.isbn) {
            node->left = insertNode(node->left, book);
        } else if (book.isbn > node->book.isbn) {
            node->right = insertNode(node->right, book);
        } else {
            return node;
        }
        
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        
        int balance = getBalance(node);
        
        if (balance > 1 && book.isbn < node->left->book.isbn) {
            return rightRotate(node);
        }
        
        if (balance < -1 && book.isbn > node->right->book.isbn) {
            return leftRotate(node);
        }
        
        if (balance > 1 && book.isbn > node->left->book.isbn) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        
        if (balance < -1 && book.isbn < node->right->book.isbn) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        
        return node;
    }
    
    AVLNode* minValueNode(AVLNode* node) {
        AVLNode* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }
    
    AVLNode* deleteNode(AVLNode* node, int isbn) {
        if (node == nullptr) {
            return node;
        }
        
        if (isbn < node->book.isbn) {
            node->left = deleteNode(node->left, isbn);
        } else if (isbn > node->book.isbn) {
            node->right = deleteNode(node->right, isbn);
        } else {
            if (node->left == nullptr || node->right == nullptr) {
                AVLNode* temp = node->left ? node->left : node->right;
                
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else {
                    node->book = temp->book;
                    node->left = temp->left;
                    node->right = temp->right;
                    node->height = temp->height;
                }
                delete temp;
            } else {
                AVLNode* temp = minValueNode(node->right);
                node->book = temp->book;
                node->right = deleteNode(node->right, temp->book.isbn);
            }
        }
        
        if (node == nullptr) {
            return node;
        }
        
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        
        int balance = getBalance(node);
        
        if (balance > 1 && getBalance(node->left) >= 0) {
            return rightRotate(node);
        }
        
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        
        if (balance < -1 && getBalance(node->right) <= 0) {
            return leftRotate(node);
        }
        
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        
        return node;
    }
    
    AVLNode* searchNode(AVLNode* node, int isbn) {
        if (node == nullptr || node->book.isbn == isbn) {
            return node;
        }
        
        if (isbn < node->book.isbn) {
            return searchNode(node->left, isbn);
        }
        
        return searchNode(node->right, isbn);
    }
    
    void inorderTraversal(AVLNode* node) {
        if (node != nullptr) {
            inorderTraversal(node->left);
            cout << "ISBN: " << node->book.isbn << ", Title: " << node->book.title;
            cout << ", Available: " << (node->book.available ? "Yes" : "No") << endl;
            inorderTraversal(node->right);
        }
    }
    
    void destroyTree(AVLNode* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
    
public:
    AVLTree() {
        root = nullptr;
    }
    
    ~AVLTree() {
        destroyTree(root);
    }
    
    void insert(int isbn, const char* title, bool available) {
        Book newBook(isbn, title, available);
        root = insertNode(root, newBook);
    }
    
    void remove(int isbn) {
        root = deleteNode(root, isbn);
    }
    
    bool search(int isbn) {
        AVLNode* result = searchNode(root, isbn);
        if (result != nullptr) {
            cout << "Book found - ISBN: " << result->book.isbn;
            cout << ", Title: " << result->book.title;
            cout << ", Available: " << (result->book.available ? "Yes" : "No") << endl;
            return true;
        } else {
            cout << "Book not found" << endl;
            return false;
        }
    }
    
    bool borrowBook(int isbn) {
        AVLNode* result = searchNode(root, isbn);
        if (result == nullptr) {
            cout << "Book not found" << endl;
            return false;
        }
        
        if (!result->book.available) {
            cout << "Book already borrowed" << endl;
            return false;
        }
        
        result->book.available = false;
        cout << "Book borrowed successfully" << endl;
        return true;
    }
    
    bool returnBook(int isbn) {
        AVLNode* result = searchNode(root, isbn);
        if (result == nullptr) {
            cout << "Book not found" << endl;
            return false;
        }
        
        if (result->book.available) {
            cout << "Book was not borrowed" << endl;
            return false;
        }
        
        result->book.available = true;
        cout << "Book returned successfully" << endl;
        return true;
    }
    
    void displayAll() {
        if (root == nullptr) {
            cout << "Library is empty" << endl;
            return;
        }
        cout << "Library Catalog:" << endl;
        inorderTraversal(root);
    }
};

int main() {
    AVLTree library;
    int choice;
    
    while (true) {
        cout << "\nLibrary Management System" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Remove Book" << endl;
        cout << "3. Search Book" << endl;
        cout << "4. Borrow Book" << endl;
        cout << "5. Return Book" << endl;
        cout << "6. Display All Books" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        
        if (choice == 1) {
            int isbn;
            char title[100];
            cout << "Enter ISBN: ";
            cin >> isbn;
            cout << "Enter Title: ";
            cin.ignore();
            cin.getline(title, 100);
            library.insert(isbn, title, true);
            cout << "Book added successfully" << endl;
        } else if (choice == 2) {
            int isbn;
            cout << "Enter ISBN: ";
            cin >> isbn;
            library.remove(isbn);
            cout << "Book removed successfully" << endl;
        } else if (choice == 3) {
            int isbn;
            cout << "Enter ISBN: ";
            cin >> isbn;
            library.search(isbn);
        } else if (choice == 4) {
            int isbn;
            cout << "Enter ISBN: ";
            cin >> isbn;
            library.borrowBook(isbn);
        } else if (choice == 5) {
            int isbn;
            cout << "Enter ISBN: ";
            cin >> isbn;
            library.returnBook(isbn);
        } else if (choice == 6) {
            library.displayAll();
        } else if (choice == 7) {
            break;
        } else {
            cout << "Invalid choice" << endl;
        }
    }
    
    return 0;
}