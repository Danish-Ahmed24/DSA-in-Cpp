#include <iostream>
#include <cmath>
using namespace std;

class Waypoint {
public:
    int id;
    double x;
    double y;
    double distance;
    string name;

    Waypoint() {
        id = 0;
        x = 0.0;
        y = 0.0;
        distance = 0.0;
        name = "";
    }

    Waypoint(int waypointId, double xCoord, double yCoord, string waypointName) {
        id = waypointId;
        x = xCoord;
        y = yCoord;
        distance = 0.0;
        name = waypointName;
    }

    void calculateDistance(double carX, double carY) {
        double dx = x - carX;
        double dy = y - carY;
        distance = sqrt(dx * dx + dy * dy);
    }
};

class Node {
public:
    Waypoint waypoint;
    Node* left;
    Node* right;
    int height;

    Node(Waypoint w) {
        waypoint = w;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

class AVLTree {
private:
    Node* root;
    double carX;
    double carY;

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

    Node* insertNode(Node* node, Waypoint waypoint) {
        if (node == nullptr) {
            return new Node(waypoint);
        }

        if (waypoint.distance < node->waypoint.distance) {
            node->left = insertNode(node->left, waypoint);
        } else if (waypoint.distance > node->waypoint.distance) {
            node->right = insertNode(node->right, waypoint);
        } else {
            if (waypoint.id < node->waypoint.id) {
                node->left = insertNode(node->left, waypoint);
            } else {
                node->right = insertNode(node->right, waypoint);
            }
        }

        updateHeight(node);

        int balance = getBalance(node);

        if (balance > 1 && waypoint.distance < node->left->waypoint.distance) {
            return rotateRight(node);
        }

        if (balance > 1 && waypoint.distance >= node->left->waypoint.distance) {
            if (waypoint.distance == node->left->waypoint.distance && waypoint.id < node->left->waypoint.id) {
                return rotateRight(node);
            }
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && waypoint.distance > node->right->waypoint.distance) {
            return rotateLeft(node);
        }

        if (balance < -1 && waypoint.distance <= node->right->waypoint.distance) {
            if (waypoint.distance == node->right->waypoint.distance && waypoint.id > node->right->waypoint.id) {
                return rotateLeft(node);
            }
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void collectWaypoints(Node* node, Waypoint*& arr, int& index) {
        if (node == nullptr) {
            return;
        }
        collectWaypoints(node->left, arr, index);
        arr[index++] = node->waypoint;
        collectWaypoints(node->right, arr, index);
    }

    Node* buildBalancedTree(Waypoint* arr, int start, int end) {
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

    int countNodes(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    void inorderTraversal(Node* node) {
        if (node == nullptr) {
            return;
        }
        inorderTraversal(node->left);
        cout << "ID: " << node->waypoint.id << ", Name: " << node->waypoint.name 
             << ", Position: (" << node->waypoint.x << ", " << node->waypoint.y 
             << "), Distance: " << node->waypoint.distance << endl;
        inorderTraversal(node->right);
    }

    void getNearestK(Node* node, int& count, int k) {
        if (node == nullptr || count >= k) {
            return;
        }
        getNearestK(node->left, count, k);
        if (count < k) {
            cout << "ID: " << node->waypoint.id << ", Name: " << node->waypoint.name 
                 << ", Position: (" << node->waypoint.x << ", " << node->waypoint.y 
                 << "), Distance: " << node->waypoint.distance << endl;
            count++;
        }
        getNearestK(node->right, count, k);
    }

public:
    AVLTree() {
        root = nullptr;
        carX = 0.0;
        carY = 0.0;
    }

    void setCarPosition(double x, double y) {
        carX = x;
        carY = y;
    }

    void addWaypoint(int id, double x, double y, string name) {
        Waypoint w(id, x, y, name);
        w.calculateDistance(carX, carY);
        root = insertNode(root, w);
    }

    void updateCarPosition(double newX, double newY) {
        cout << "\n=== Updating Car Position from (" << carX << ", " << carY 
             << ") to (" << newX << ", " << newY << ") ===" << endl;
        
        carX = newX;
        carY = newY;

        int totalNodes = countNodes(root);
        if (totalNodes == 0) {
            return;
        }

        Waypoint* waypoints = new Waypoint[totalNodes];
        int index = 0;
        collectWaypoints(root, waypoints, index);

        for (int i = 0; i < totalNodes; i++) {
            waypoints[i].calculateDistance(carX, carY);
        }

        for (int i = 0; i < totalNodes - 1; i++) {
            for (int j = 0; j < totalNodes - i - 1; j++) {
                if (waypoints[j].distance > waypoints[j + 1].distance || 
                    (waypoints[j].distance == waypoints[j + 1].distance && waypoints[j].id > waypoints[j + 1].id)) {
                    Waypoint temp = waypoints[j];
                    waypoints[j] = waypoints[j + 1];
                    waypoints[j + 1] = temp;
                }
            }
        }

        root = buildBalancedTree(waypoints, 0, totalNodes - 1);

        delete[] waypoints;
    }

    void displayNearestLocations(int k) {
        cout << "\nNearest " << k << " Locations:" << endl;
        int count = 0;
        getNearestK(root, count, k);
    }

    void displayAllWaypoints() {
        cout << "\nAll Waypoints (sorted by distance):" << endl;
        inorderTraversal(root);
    }

    void getCurrentPosition() {
        cout << "Current Car Position: (" << carX << ", " << carY << ")" << endl;
    }
};

int main() {
    AVLTree navSystem;

    navSystem.setCarPosition(0.0, 0.0);
    navSystem.getCurrentPosition();

    cout << "\nAdding waypoints..." << endl;
    navSystem.addWaypoint(1, 5.0, 5.0, "Restaurant");
    navSystem.addWaypoint(2, 10.0, 2.0, "Gas Station");
    navSystem.addWaypoint(3, 3.0, 4.0, "Hospital");
    navSystem.addWaypoint(4, 8.0, 8.0, "Park");
    navSystem.addWaypoint(5, 2.0, 1.0, "Pharmacy");
    navSystem.addWaypoint(6, 12.0, 5.0, "Mall");

    navSystem.displayAllWaypoints();
    navSystem.displayNearestLocations(3);

    navSystem.updateCarPosition(6.0, 3.0);
    navSystem.displayAllWaypoints();
    navSystem.displayNearestLocations(3);

    navSystem.updateCarPosition(10.0, 10.0);
    navSystem.displayAllWaypoints();
    navSystem.displayNearestLocations(3);

    return 0;
}