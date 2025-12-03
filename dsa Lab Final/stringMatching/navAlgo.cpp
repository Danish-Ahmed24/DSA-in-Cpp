#include <iostream>
using namespace std;

// Function to perform naive string matching
void naiveSearch(char text[], char pattern[]) {
    int n = 0;
    while (text[n] != '\0') n++;   // length of text

    int m = 0;
    while (pattern[m] != '\0') m++; // length of pattern

    bool found = false;

    // Slide pattern over text one by one
    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j])
                break;  // mismatch found
        }

        if (j == m) {  // pattern found
            cout << "Pattern found at index " << i << endl;
            found = true;
        }
    }

    if (!found)
        cout << "Pattern not found in text." << endl;
}

int main() {
    char text[] = "ABABABCABABABCABABABC";
    char pattern[] = "ABABC";

    cout << "Text: " << text << endl;
    cout << "Pattern: " << pattern << endl;

    naiveSearch(text, pattern);

    return 0;
}