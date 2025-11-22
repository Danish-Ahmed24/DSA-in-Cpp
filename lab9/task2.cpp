#include <iostream>
using namespace std;

class Appointment {
public:
    int startTime;
    int duration;
    int endTime;
    char doctorName[100];
    
    Appointment() {
        startTime = 0;
        duration = 0;
        endTime = 0;
        doctorName[0] = '\0';
    }
    
    Appointment(int st, int dur, const char* name) {
        startTime = st;
        duration = dur;
        endTime = st + dur;
        int i = 0;
        while (name[i] != '\0' && i < 99) {
            doctorName[i] = name[i];
            i++;
        }
        doctorName[i] = '\0';
    }
};

class AVLNode {
public:
    Appointment appointment;
    AVLNode* left;
    AVLNode* right;
    int height;
    
    AVLNode() {
        left = nullptr;
        right = nullptr;
        height = 1;
    }
    
    AVLNode(Appointment app) {
        appointment = app;
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
    
    bool checkConflictInTree(AVLNode* node, int start, int end) {
        if (node == nullptr) {
            return false;
        }
        
        if (start < node->appointment.endTime && end > node->appointment.startTime) {
            return true;
        }
        
        bool leftConflict = checkConflictInTree(node->left, start, end);
        if (leftConflict) {
            return true;
        }
        
        bool rightConflict = checkConflictInTree(node->right, start, end);
        return rightConflict;
    }
    
    AVLNode* insertNode(AVLNode* node, Appointment app) {
        if (node == nullptr) {
            return new AVLNode(app);
        }
        
        if (app.startTime < node->appointment.startTime) {
            node->left = insertNode(node->left, app);
        } else if (app.startTime > node->appointment.startTime) {
            node->right = insertNode(node->right, app);
        } else {
            return node;
        }
        
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        
        int balance = getBalance(node);
        
        if (balance > 1 && app.startTime < node->left->appointment.startTime) {
            return rightRotate(node);
        }
        
        if (balance < -1 && app.startTime > node->right->appointment.startTime) {
            return leftRotate(node);
        }
        
        if (balance > 1 && app.startTime > node->left->appointment.startTime) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        
        if (balance < -1 && app.startTime < node->right->appointment.startTime) {
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
    
    AVLNode* deleteNode(AVLNode* node, int startTime) {
        if (node == nullptr) {
            return node;
        }
        
        if (startTime < node->appointment.startTime) {
            node->left = deleteNode(node->left, startTime);
        } else if (startTime > node->appointment.startTime) {
            node->right = deleteNode(node->right, startTime);
        } else {
            if (node->left == nullptr || node->right == nullptr) {
                AVLNode* temp = node->left ? node->left : node->right;
                
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else {
                    node->appointment = temp->appointment;
                    node->left = temp->left;
                    node->right = temp->right;
                    node->height = temp->height;
                }
                delete temp;
            } else {
                AVLNode* temp = minValueNode(node->right);
                node->appointment = temp->appointment;
                node->right = deleteNode(node->right, temp->appointment.startTime);
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
    
    AVLNode* searchNode(AVLNode* node, int startTime) {
        if (node == nullptr || node->appointment.startTime == startTime) {
            return node;
        }
        
        if (startTime < node->appointment.startTime) {
            return searchNode(node->left, startTime);
        }
        
        return searchNode(node->right, startTime);
    }
    
    void inorderTraversal(AVLNode* node) {
        if (node != nullptr) {
            inorderTraversal(node->left);
            cout << "Start Time: " << node->appointment.startTime;
            cout << ", Duration: " << node->appointment.duration;
            cout << ", Doctor: " << node->appointment.doctorName << endl;
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
    
    bool insertAppointment(int startTime, int duration, const char* doctorName) {
        int endTime = startTime + duration;
        
        if (checkConflictInTree(root, startTime, endTime)) {
            cout << "Conflict detected! Appointment overlaps with existing appointment" << endl;
            return false;
        }
        
        Appointment newApp(startTime, duration, doctorName);
        root = insertNode(root, newApp);
        cout << "Appointment scheduled successfully" << endl;
        return true;
    }
    
    bool cancelAppointment(int startTime) {
        AVLNode* result = searchNode(root, startTime);
        if (result == nullptr) {
            cout << "Appointment not found" << endl;
            return false;
        }
        
        root = deleteNode(root, startTime);
        cout << "Appointment cancelled successfully" << endl;
        return true;
    }
    
    bool checkConflict(int startTime, int duration) {
        int endTime = startTime + duration;
        
        if (checkConflictInTree(root, startTime, endTime)) {
            cout << "Conflict exists! Time slot overlaps with existing appointment" << endl;
            return true;
        } else {
            cout << "No conflict! Time slot is available" << endl;
            return false;
        }
    }
    
    void displayAll() {
        if (root == nullptr) {
            cout << "No appointments scheduled" << endl;
            return;
        }
        cout << "All Appointments:" << endl;
        inorderTraversal(root);
    }
};

int main() {
    AVLTree appointments;
    int choice;
    
    while (true) {
        cout << "\nHospital Appointment Management System" << endl;
        cout << "1. Schedule Appointment" << endl;
        cout << "2. Cancel Appointment" << endl;
        cout << "3. Check for Conflict" << endl;
        cout << "4. Display All Appointments" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        
        if (choice == 1) {
            int startTime, duration;
            char doctorName[100];
            cout << "Enter start time: ";
            cin >> startTime;
            cout << "Enter duration: ";
            cin >> duration;
            cout << "Enter doctor name: ";
            cin.ignore();
            cin.getline(doctorName, 100);
            appointments.insertAppointment(startTime, duration, doctorName);
        } else if (choice == 2) {
            int startTime;
            cout << "Enter start time of appointment to cancel: ";
            cin >> startTime;
            appointments.cancelAppointment(startTime);
        } else if (choice == 3) {
            int startTime, duration;
            cout << "Enter start time: ";
            cin >> startTime;
            cout << "Enter duration: ";
            cin >> duration;
            appointments.checkConflict(startTime, duration);
        } else if (choice == 4) {
            appointments.displayAll();
        } else if (choice == 5) {
            break;
        } else {
            cout << "Invalid choice" << endl;
        }
    }
    
    return 0;
}