#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <climits>
#include <iomanip>
using namespace std;

// Structure to represent an edge with neighbor and distance
struct Edge {
    string neighbor;
    int distance;
    
    Edge(string n, int d) : neighbor(n), distance(d) {}
};

// Structure for priority queue (min-heap based on distance)
struct PQNode {
    string city;
    int distance;
    
    PQNode(string c, int d) : city(c), distance(d) {}
    
    // Comparison operator for min-heap (greater distance = lower priority)
    bool operator>(const PQNode& other) const {
        return distance > other.distance;
    }
};

class CityRouteFinder {
private:
    // Graph represented as adjacency list using unordered_map
    unordered_map<string, vector<Edge>> graph;
    
    // Convert string to lowercase for case-insensitive operations
    string toLowercase(string str) {
        transform(str.begin(), str.end(), str.begin(), ::tolower);
        return str;
    }
    
    // Check if city exists in the graph
    bool cityExists(const string& city) {
        return graph.find(city) != graph.end();
    }
    
    // DFS Helper function
    void dfsHelper(const string& city, unordered_map<string, bool>& visited) {
        cout << city << " ";
        visited[city] = true;
        
        for (const Edge& edge : graph[city]) {
            if (!visited[edge.neighbor]) {
                dfsHelper(edge.neighbor, visited);
            }
        }
    }
    
    // BFS Helper function
    void bfsHelper(const string& startCity) {
        unordered_map<string, bool> visited;
        queue<string> q;
        
        q.push(startCity);
        visited[startCity] = true;
        
        cout << "\nBFS Traversal from " << startCity << ": ";
        
        while (!q.empty()) {
            string current = q.front();
            q.pop();
            cout << current << " ";
            
            for (const Edge& edge : graph[current]) {
                if (!visited[edge.neighbor]) {
                    visited[edge.neighbor] = true;
                    q.push(edge.neighbor);
                }
            }
        }
        cout << endl;
    }
    
public:
    // Add bidirectional edge between two cities
    void addEdge(string city1, string city2, int distance) {
        if (distance <= 0) {
            cout << "Error: Distance must be positive!" << endl;
            return;
        }
        
        city1 = toLowercase(city1);
        city2 = toLowercase(city2);
        
        if (city1 == city2) {
            cout << "Error: Cannot add edge from city to itself!" << endl;
            return;
        }
        
        // Add edge from city1 to city2
        graph[city1].push_back(Edge(city2, distance));
        
        // Add edge from city2 to city1 (undirected graph)
        graph[city2].push_back(Edge(city1, distance));
        
        cout << "✓ Edge added: " << city1 << " <-> " << city2 
             << " (Distance: " << distance << " km)" << endl;
    }
    
    // Remove edge between two cities
    void removeEdge(string city1, string city2) {
        city1 = toLowercase(city1);
        city2 = toLowercase(city2);
        
        if (!cityExists(city1) || !cityExists(city2)) {
            cout << "Error: One or both cities not found!" << endl;
            return;
        }
        
        // Remove edge from city1 to city2
        auto& edges1 = graph[city1];
        edges1.erase(remove_if(edges1.begin(), edges1.end(),
            [&city2](const Edge& e) { return e.neighbor == city2; }), edges1.end());
        
        // Remove edge from city2 to city1
        auto& edges2 = graph[city2];
        edges2.erase(remove_if(edges2.begin(), edges2.end(),
            [&city1](const Edge& e) { return e.neighbor == city1; }), edges2.end());
        
        cout << "✓ Edge removed between " << city1 << " and " << city2 << endl;
    }
    
    // Display all cities in the graph
    void displayAllCities() {
        if (graph.empty()) {
            cout << "No cities added yet!" << endl;
            return;
        }
        
        cout << "\n============ All Cities (" << graph.size() << ") ============" << endl;
        int count = 1;
        for (const auto& pair : graph) {
            cout << setw(2) << count++ << ". " << pair.first 
                 << " (Connections: " << pair.second.size() << ")" << endl;
        }
        cout << "===========================================" << endl;
    }
    
    // Display all connections in the graph
    void displayAllConnections() {
        if (graph.empty()) {
            cout << "No cities added yet!" << endl;
            return;
        }
        
        cout << "\n========== All City Connections ==========" << endl;
        for (const auto& pair : graph) {
            cout << pair.first << " → ";
            if (pair.second.empty()) {
                cout << "(No connections)";
            } else {
                for (size_t i = 0; i < pair.second.size(); i++) {
                    if (i > 0) cout << ", ";
                    cout << pair.second[i].neighbor << "(" 
                         << pair.second[i].distance << "km)";
                }
            }
            cout << endl;
        }
        cout << "==========================================" << endl;
    }
    
    // DFS Traversal
    void dfsTraversal(string startCity) {
        startCity = toLowercase(startCity);
        
        if (!cityExists(startCity)) {
            cout << "Error: City '" << startCity << "' not found!" << endl;
            return;
        }
        
        unordered_map<string, bool> visited;
        cout << "\nDFS Traversal from " << startCity << ": ";
        dfsHelper(startCity, visited);
        cout << endl;
    }
    
    // BFS Traversal
    void bfsTraversal(string startCity) {
        startCity = toLowercase(startCity);
        
        if (!cityExists(startCity)) {
            cout << "Error: City '" << startCity << "' not found!" << endl;
            return;
        }
        
        bfsHelper(startCity);
    }
    
    // Dijkstra's Algorithm to find shortest path
    void findShortestPath(string source, string destination) {
        source = toLowercase(source);
        destination = toLowercase(destination);
        
        if (!cityExists(source) || !cityExists(destination)) {
            cout << "Error: Invalid source or destination city!" << endl;
            return;
        }
        
        if (source == destination) {
            cout << "Source and destination are the same!" << endl;
            return;
        }
        
        // Initialize distances and parent map
        unordered_map<string, int> distances;
        unordered_map<string, string> parent;
        
        for (const auto& pair : graph) {
            distances[pair.first] = INT_MAX;
        }
        distances[source] = 0;
        
        // Priority queue (min-heap)
        priority_queue<PQNode, vector<PQNode>, greater<PQNode>> pq;
        pq.push(PQNode(source, 0));
        
        unordered_map<string, bool> visited;
        
        // Dijkstra's main loop
        while (!pq.empty()) {
            PQNode current = pq.top();
            pq.pop();
            
            string currentCity = current.city;
            
            if (visited[currentCity]) continue;
            visited[currentCity] = true;
            
            // Early exit if we reached destination
            if (currentCity == destination) break;
            
            // Process all neighbors
            for (const Edge& edge : graph[currentCity]) {
                string neighbor = edge.neighbor;
                int weight = edge.distance;
                
                int newDist = distances[currentCity] + weight;
                
                if (newDist < distances[neighbor]) {
                    distances[neighbor] = newDist;
                    parent[neighbor] = currentCity;
                    pq.push(PQNode(neighbor, newDist));
                }
            }
        }
        
        // Check if path exists
        if (distances[destination] == INT_MAX) {
            cout << "\nNo path exists between " << source 
                 << " and " << destination << "!" << endl;
            return;
        }
        
        // Reconstruct path using stack
        stack<string> pathStack;
        string current = destination;
        
        while (!current.empty()) {
            pathStack.push(current);
            current = parent[current];
        }
        
        // Display results
        cout << "\n=========================================" << endl;
        cout << "        SHORTEST PATH FOUND              " << endl;
        cout << "=========================================" << endl;
        cout << "Source:      " << source << endl;
        cout << "Destination: " << destination << endl;
        cout << "Distance:    " << distances[destination] << " km" << endl;
        cout << "\nRoute: ";
        
        bool first = true;
        while (!pathStack.empty()) {
            if (!first) cout << " → ";
            cout << pathStack.top();
            pathStack.pop();
            first = false;
        }
        cout << "\n===========================================" << endl;
    }
    
    // Find all paths between two cities (for analysis)
    void findAllPaths(string source, string destination) {
        source = toLowercase(source);
        destination = toLowercase(destination);
        
        if (!cityExists(source) || !cityExists(destination)) {
            cout << "Error: Invalid source or destination city!" << endl;
            return;
        }
        
        vector<vector<string>> allPaths;
        vector<string> currentPath;
        unordered_map<string, bool> visited;
        
        findAllPathsHelper(source, destination, visited, currentPath, allPaths);
        
        if (allPaths.empty()) {
            cout << "\nNo paths exist between " << source << " and " << destination << endl;
            return;
        }
        
        cout << "\n========== All Paths from " << source << " to " << destination << " ==========" << endl;
        for (size_t i = 0; i < allPaths.size(); i++) {
            cout << "Path " << (i + 1) << ": ";
            for (size_t j = 0; j < allPaths[i].size(); j++) {
                if (j > 0) cout << " → ";
                cout << allPaths[i][j];
            }
            cout << endl;
        }
        cout << "Total paths found: " << allPaths.size() << endl;
        cout << "==========================================" << endl;
    }
    
private:
    void findAllPathsHelper(const string& current, const string& destination,
                           unordered_map<string, bool>& visited,
                           vector<string>& currentPath,
                           vector<vector<string>>& allPaths) {
        visited[current] = true;
        currentPath.push_back(current);
        
        if (current == destination) {
            allPaths.push_back(currentPath);
        } else {
            for (const Edge& edge : graph[current]) {
                if (!visited[edge.neighbor]) {
                    findAllPathsHelper(edge.neighbor, destination, visited, currentPath, allPaths);
                }
            }
        }
        
        currentPath.pop_back();
        visited[current] = false;
    }
    
public:
    // Get statistics about the graph
    void displayStatistics() {
        if (graph.empty()) {
            cout << "No cities in the graph!" << endl;
            return;
        }
        
        int totalEdges = 0;
        int maxConnections = 0;
        string mostConnectedCity;
        
        for (const auto& pair : graph) {
            totalEdges += pair.second.size();
            if (pair.second.size() > maxConnections) {
                maxConnections = pair.second.size();
                mostConnectedCity = pair.first;
            }
        }
        
        totalEdges /= 2; // Undirected graph
        
        cout << "\n========== Graph Statistics ==========" << endl;
        cout << "Total Cities:           " << graph.size() << endl;
        cout << "Total Connections:      " << totalEdges << endl;
        cout << "Most Connected City:    " << mostConnectedCity 
             << " (" << maxConnections << " connections)" << endl;
        cout << "======================================" << endl;
    }
};

void displayMenu() {
    cout << "\n=========================================" << endl;
    cout << "       CITY ROUTE FINDER MENU            " << endl;
    cout << "=========================================" << endl;
    cout << " 1. Add Edge (City Connection)           " << endl;
    cout << " 2. Remove Edge                          " << endl;
    cout << " 3. Display All Cities                   " << endl;
    cout << " 4. Display All Connections              " << endl;
    cout << " 5. Find Shortest Path (Dijkstra)        " << endl;
    cout << " 6. Find All Paths                       " << endl;
    cout << " 7. DFS Traversal                        " << endl;
    cout << " 8. BFS Traversal                        " << endl;
    cout << " 9. Display Graph Statistics             " << endl;
    cout << " 0. Exit                                 " << endl;
    cout << "=========================================" << endl;
    cout << "Enter your choice: ";
}

int main() {
    CityRouteFinder graph;
    
    cout << "\n=========================================" << endl;
    cout << "   WELCOME TO CITY ROUTE FINDER          " << endl;
    cout << "=========================================" << endl;
    
    cout << "\n=== Loading Demo Data ===" << endl;
    
    // Demo data - Pakistan cities
    graph.addEdge("Karachi", "Lahore", 1200);
    graph.addEdge("Lahore", "Islamabad", 380);
    graph.addEdge("Islamabad", "Peshawar", 180);
    graph.addEdge("Karachi", "Multan", 900);
    graph.addEdge("Multan", "Lahore", 340);
    graph.addEdge("Peshawar", "Lahore", 450);
    graph.addEdge("Karachi", "Hyderabad", 160);
    graph.addEdge("Hyderabad", "Multan", 800);
    graph.addEdge("Islamabad", "Multan", 550);
    graph.addEdge("Karachi", "Quetta", 680);
    
    cout << "\n=== Demo Data Loaded Successfully ===" << endl;
    
    int choice;
    string city1, city2;
    int distance;
    
    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1: {
                cout << "Enter first city: ";
                getline(cin, city1);
                cout << "Enter second city: ";
                getline(cin, city2);
                cout << "Enter distance (km): ";
                cin >> distance;
                graph.addEdge(city1, city2, distance);
                break;
            }
            
            case 2: {
                cout << "Enter first city: ";
                getline(cin, city1);
                cout << "Enter second city: ";
                getline(cin, city2);
                graph.removeEdge(city1, city2);
                break;
            }
            
            case 3:
                graph.displayAllCities();
                break;
                
            case 4:
                graph.displayAllConnections();
                break;
                
            case 5: {
                cout << "Enter source city: ";
                getline(cin, city1);
                cout << "Enter destination city: ";
                getline(cin, city2);
                graph.findShortestPath(city1, city2);
                break;
            }
            
            case 6: {
                cout << "Enter source city: ";
                getline(cin, city1);
                cout << "Enter destination city: ";
                getline(cin, city2);
                graph.findAllPaths(city1, city2);
                break;
            }
            
            case 7: {
                cout << "Enter starting city for DFS: ";
                getline(cin, city1);
                graph.dfsTraversal(city1);
                break;
            }
            
            case 8: {
                cout << "Enter starting city for BFS: ";
                getline(cin, city1);
                graph.bfsTraversal(city1);
                break;
            }
            
            case 9:
                graph.displayStatistics();
                break;
            
            case 0:
                cout << "\n=========================================" << endl;
                cout << "   Thank you for using Route Finder!     " << endl;
                cout << "=========================================\n" << endl;
                return 0;
                
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }
    
    return 0;
}