#include <iostream>
using namespace std;

#define d 256    // Number of characters in input alphabet
#define q 101    // A prime number for modulus

// Rabin-Karp search function
void rabinKarpSearch(char text[], char pattern[]) {
    int n = 0, m = 0;

    while (text[n] != '\0') n++;       // length of text
    while (pattern[m] != '\0') m++;   // length of pattern

    int i, j;
    int p = 0;  // hash value for pattern
    int t = 0;  // hash value for text
    int h = 1;

    // The value of h would be "pow(d, m-1) % q"
    for (i = 0; i < m - 1; i++)
        h = (h * d) % q;

    // Calculate hash value for pattern and first window of text
    for (i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // Slide the pattern over text one by one
    for (i = 0; i <= n - m; i++) {
        // Check the hash values
        if (p == t) {
            // If hash matches, check characters one by one
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }
            if (j == m)
                cout << "Pattern found at index " << i << endl;
        }

        // Calculate hash value for next window
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;

            // Make sure t is positive
            if (t < 0)
                t = (t + q);
        }
    }
}

int main() {
    char text[] = "ABCDEABCDEABCDE";
    char pattern[] = "EDCBA";

    cout << "Text: " << text << endl;
    cout << "Pattern: " << pattern << endl;

    rabinKarpSearch(text, pattern);

    return 0;
}