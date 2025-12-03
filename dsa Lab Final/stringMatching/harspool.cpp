#include <iostream>
#include <cstring>
using namespace std;

#define CHAR_SIZE 256  // total possible characters

// Preprocessing: create the shift table
void createShiftTable(char pattern[], int m, int shiftTable[]) {
    // Initialize all shifts to pattern length
    for (int i = 0; i < CHAR_SIZE; i++)
        shiftTable[i] = m;

    // Fill shifts based on pattern
    for (int i = 0; i < m - 1; i++)
        shiftTable[(int)pattern[i]] = m - 1 - i;
}

// Horspool search function
void horspoolSearch(char text[], char pattern[]) {
    int n = strlen(text);
    int m = strlen(pattern);

    int shiftTable[CHAR_SIZE];
    createShiftTable(pattern, m, shiftTable);

    int i = m - 1;  // index in text
    while (i < n) {
        int k = 0;
        // Compare pattern from right to left
        while (k < m && pattern[m - 1 - k] == text[i - k])
            k++;

        if (k == m) {
            cout << "Pattern found at index " << (i - m + 1) << endl;
        }

        // Shift according to the character after the window
        i += shiftTable[(int)text[i]];
    }
}

int main() {
    char text[] = "THE_UNIVERSITY_IS_HERE";
    char pattern[] = "UNIVERSITY";

    cout << "Text: " << text << endl;
    cout << "Pattern: " << pattern << endl << endl;

    horspoolSearch(text, pattern);

    return 0;
}