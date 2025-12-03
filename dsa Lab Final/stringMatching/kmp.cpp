#include <iostream>
using namespace std;

// Function to compute LPS (Longest Prefix Suffix) array
void computeLPS(char pattern[], int m, int lps[]) {
    int length = 0; // length of previous longest prefix suffix
    lps[0] = 0;     // lps[0] is always 0

    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1]; // fall back
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP search function
void KMPSearch(char text[], char pattern[]) {
    int n = 0; // length of text
    while (text[n] != '\0') n++;

    int m = 0; // length of pattern
    while (pattern[m] != '\0') m++;

    int lps[m];
    computeLPS(pattern, m, lps);

    int i = 0; // index for text[]
    int j = 0; // index for pattern[]

    bool found = false;

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            cout << "Pattern found at index " << i - j << endl;
            found = true;
            j = lps[j - 1]; // continue searching
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
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

    KMPSearch(text, pattern);

    return 0;
}