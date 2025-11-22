#include <iostream>
#include <string>
using namespace std;

int h, w;
bool found = false;
char targetGrid[20][20];


bool isEqual(char a[20][20], char b[20][20]) {
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            if (a[i][j] != b[i][j])
                return false;
    return true;
}


void tilt(char grid[20][20], string dir, char newGrid[20][20]) {
    
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            newGrid[i][j] = '.';

    if (dir == "left") {
        for (int i = 0; i < h; i++) {
            int pos = 0;
            for (int j = 0; j < w; j++) {
                if (grid[i][j] != '.')
                    newGrid[i][pos++] = grid[i][j];
            }
        }
    } else if (dir == "right") {
        for (int i = 0; i < h; i++) {
            int pos = w - 1;
            for (int j = w - 1; j >= 0; j--) {
                if (grid[i][j] != '.')
                    newGrid[i][pos--] = grid[i][j];
            }
        }
    } else if (dir == "up") {
        for (int j = 0; j < w; j++) {
            int pos = 0;
            for (int i = 0; i < h; i++) {
                if (grid[i][j] != '.')
                    newGrid[pos++][j] = grid[i][j];
            }
        }
    } else if (dir == "down") {
        for (int j = 0; j < w; j++) {
            int pos = h - 1;
            for (int i = h - 1; i >= 0; i--) {
                if (grid[i][j] != '.')
                    newGrid[pos--][j] = grid[i][j];
            }
        }
    }
}



void solve(char grid[20][20], int depth = 0) {
    if (isEqual(grid, targetGrid)) {
        found = true;
        return;
    }
    if (depth > 10) return; 

    string dirs[4] = {"left", "right", "up", "down"};
    for (int i = 0; i < 4; i++) {
        char newGrid[20][20];
        tilt(grid, dirs[i], newGrid);
        solve(newGrid, depth + 1);
        if (found) return;
    }
}

int main() {
    cout << "Enter grid height and width: ";
    cin >> h >> w;

    char startGrid[20][20];
    cout << "Enter start grid:\n";
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            cin >> startGrid[i][j];

    cout << "Enter target grid:\n";
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            cin >> targetGrid[i][j];

    solve(startGrid);

    if (found)
        cout << "yes\n";
    else
        cout << "no\n";

    return 0;
}
