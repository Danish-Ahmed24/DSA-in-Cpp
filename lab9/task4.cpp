    #include <iostream>
using namespace std;

class Student {
public:
    int id;
    double gpa;
    string name;

    Student() {
        id = 0;
        gpa = 0.0;
        name = "";
    }

    Student(int studentId, double studentGpa, string studentName) {
        id = studentId;
        gpa = studentGpa;
        name = studentName;
    }
};

class Node {
public:
    Student student;
    Node* left;
    Node* right;
    int height;

    Node(Student s) {
        student = s;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

class AVLTree {
private:
    Node* root;
    int totalStudents;
    double totalGPA;

    int getHeight(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    int getBalance(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    void updateHeight(Node* node) {
        if (node == nullptr) {
            return;
        }
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* insertNode(Node* node, Student student) {
        if (node == nullptr) {
            totalStudents++;
            totalGPA += student.gpa;
            return new Node(student);
        }

        if (student.gpa < node->student.gpa) {
            node->left = insertNode(node->left, student);
        } else if (student.gpa > node->student.gpa) {
            node->right = insertNode(node->right, student);
        } else {
            if (student.id < node->student.id) {
                node->left = insertNode(node->left, student);
            } else {
                node->right = insertNode(node->right, student);
            }
        }

        updateHeight(node);

        int balance = getBalance(node);

        if (balance > 1 && student.gpa < node->left->student.gpa) {
            return rotateRight(node);
        }

        if (balance > 1 && student.gpa >= node->left->student.gpa) {
            if (student.gpa == node->left->student.gpa && student.id < node->left->student.id) {
                return rotateRight(node);
            }
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && student.gpa > node->right->student.gpa) {
            return rotateLeft(node);
        }

        if (balance < -1 && student.gpa <= node->right->student.gpa) {
            if (student.gpa == node->right->student.gpa && student.id > node->right->student.id) {
                return rotateLeft(node);
            }
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void collectStudents(Node* node, Student*& arr, int& index) {
        if (node == nullptr) {
            return;
        }
        collectStudents(node->left, arr, index);
        arr[index++] = node->student;
        collectStudents(node->right, arr, index);
    }

    Node* buildBalancedTree(Student* arr, int start, int end) {
        if (start > end) {
            return nullptr;
        }

        int mid = (start + end) / 2;
        Node* node = new Node(arr[mid]);

        node->left = buildBalancedTree(arr, start, mid - 1);
        node->right = buildBalancedTree(arr, mid + 1, end);

        updateHeight(node);

        return node;
    }

    void inorderTraversal(Node* node) {
        if (node == nullptr) {
            return;
        }
        inorderTraversal(node->left);
        cout << "ID: " << node->student.id << ", Name: " << node->student.name 
             << ", GPA: " << node->student.gpa << endl;
        inorderTraversal(node->right);
    }

    void reverseInorder(Node* node, int& count, int k) {
        if (node == nullptr || count >= k) {
            return;
        }
        reverseInorder(node->right, count, k);
        if (count < k) {
            cout << "ID: " << node->student.id << ", Name: " << node->student.name 
                 << ", GPA: " << node->student.gpa << endl;
            count++;
        }
        reverseInorder(node->left, count, k);
    }

    int countNodes(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

public:
    AVLTree() {
        root = nullptr;
        totalStudents = 0;
        totalGPA = 0.0;
    }

    void insert(int id, double gpa, string name) {
        Student s(id, gpa, name);
        root = insertNode(root, s);
    }

    void mergeWith(AVLTree& other) {
        int size1 = countNodes(root);
        int size2 = countNodes(other.root);
        int totalSize = size1 + size2;

        if (totalSize == 0) {
            return;
        }

        Student* arr = new Student[totalSize];
        int index = 0;

        collectStudents(root, arr, index);
        collectStudents(other.root, arr, index);

        for (int i = 0; i < totalSize - 1; i++) {
            for (int j = 0; j < totalSize - i - 1; j++) {
                if (arr[j].gpa > arr[j + 1].gpa || 
                    (arr[j].gpa == arr[j + 1].gpa && arr[j].id > arr[j + 1].id)) {
                    Student temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }

        totalStudents = 0;
        totalGPA = 0.0;
        for (int i = 0; i < totalSize; i++) {
            totalGPA += arr[i].gpa;
        }
        totalStudents = totalSize;

        root = buildBalancedTree(arr, 0, totalSize - 1);

        delete[] arr;
    }

    void displayTopPerformers(int k) {
        cout << "\nTop " << k << " Performers:" << endl;
        int count = 0;
        reverseInorder(root, count, k);
    }

    double getAverageGPA() {
        if (totalStudents == 0) {
            return 0.0;
        }
        return totalGPA / totalStudents;
    }

    void display() {
        inorderTraversal(root);
    }

    int getStudentCount() {
        return totalStudents;
    }
};

int main() {
    AVLTree csTree;
    cout << "Computer Science Department:" << endl;
    csTree.insert(101, 3.8, "Alice");
    csTree.insert(102, 3.9, "Bob");
    csTree.insert(103, 3.5, "Charlie");
    csTree.insert(104, 3.7, "David");
    csTree.display();
    cout << "Average GPA: " << csTree.getAverageGPA() << endl;

    AVLTree mathTree;
    cout << "\nMathematics Department:" << endl;
    mathTree.insert(201, 3.6, "Eve");
    mathTree.insert(202, 4.0, "Frank");
    mathTree.insert(203, 3.4, "Grace");
    mathTree.insert(204, 3.85, "Henry");
    mathTree.display();
    cout << "Average GPA: " << mathTree.getAverageGPA() << endl;

    cout << "\n=== Merging Departments ===" << endl;
    csTree.mergeWith(mathTree);

    cout << "\nMerged Department:" << endl;
    csTree.display();
    cout << "\nTotal Students: " << csTree.getStudentCount() << endl;
    cout << "Average GPA: " << csTree.getAverageGPA() << endl;

    csTree.displayTopPerformers(3);

    return 0;
}