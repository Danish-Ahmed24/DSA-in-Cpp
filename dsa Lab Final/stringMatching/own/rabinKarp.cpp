#include <iostream>
#include <string>
using namespace std;

#define ALPHABET_SIZE 256
#define PRIME 101     // A prime number for hashing

void rabinKarp(string text, string pattern) {

    int textLength = text.length();
    int patternLength = pattern.length();

    int patternHash = 0;        // Hash of pattern
    int windowHash = 0;         // Hash of current window in text
    int hashPower = 1;          // (ALPHABET_SIZE^(patternLength-1)) % PRIME

    // Precompute power for leftmost char
    for (int i = 0; i < patternLength - 1; i++)
        hashPower = (hashPower * ALPHABET_SIZE) % PRIME;

    // Compute initial hash values
    for (int i = 0; i < patternLength; i++) {
        patternHash = (ALPHABET_SIZE * patternHash + pattern[i]) % PRIME;
        windowHash  = (ALPHABET_SIZE * windowHash  + text[i]) % PRIME;
    }

    // Slide the pattern over the text
    for (int index = 0; index <= textLength - patternLength; index++) {

        // If hash matches, check characters
        if (patternHash == windowHash) {
            bool matched = true;
            for (int j = 0; j < patternLength; j++) {
                if (text[index + j] != pattern[j]) {
                    matched = false;
                    break;
                }
            }
            if (matched) {
                cout << "Pattern found at index " << index << "\n";
            }
        }

        // Compute hash for next window
        if (index < textLength - patternLength) {
            windowHash = (ALPHABET_SIZE * (windowHash - text[index] * hashPower)
                          + text[index + patternLength]) % PRIME;

            if (windowHash < 0)
                windowHash += PRIME;
        }
    }
}

int main() {
    string text = "ABCCDDAEFG";
    string pattern = "CDD";
    rabinKarp(text, pattern);
}
