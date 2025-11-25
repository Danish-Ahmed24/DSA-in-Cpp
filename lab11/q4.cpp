#include <iostream>
using namespace std;

int strLength(const char s[]) {
    int i = 0;
    while (s[i] != '\0') i++;
    return i;
}

void readLine(char s[], int maxLen) {
    int i = 0;
    char c;
    while (true) {
        c = cin.get();
        if (c == '\n' || c == '\r' || c == EOF) break;
        if (i < maxLen - 1) {
            s[i] = c;
            i++;
        }
    }
    s[i] = '\0';
}

int main() {
    const int MAX_TEXT = 1000;
    const int MAX_PATTERN = 200;
    char text[MAX_TEXT];
    char pattern[MAX_PATTERN];

    readLine(text, MAX_TEXT);
    readLine(pattern, MAX_PATTERN);

    int n = strLength(text);
    int m = strLength(pattern);

    if (m == 0 || n == 0 || m > n) {
        return 0;
    }

    long long base = 256;
    long long mod = 1000000007;
    long long h = 1;
    int i = 0;
    while (i < m - 1) {
        h = (h * base) % mod;
        i++;
    }

    long long pHash = 0;
    long long tHash = 0;

    i = 0;
    while (i < m) {
        pHash = (pHash * base + (unsigned char)pattern[i]) % mod;
        tHash = (tHash * base + (unsigned char)text[i]) % mod;
        i++;
    }

    int idxArr[1000];
    int idxCount = 0;

    int s = 0;
    while (s <= n - m) {
        if (pHash == tHash) {
            int j = 0;
            while (j < m && text[s + j] == pattern[j]) j++;
            if (j == m) {
                idxArr[idxCount] = s;
                idxCount++;
            }
        }
        if (s < n - m) {
            long long val1 = tHash - (long long)text[s] * h % mod;
            if (val1 < 0) val1 += mod;
            long long val2 = val1 * base + (unsigned char)text[s + m];
            tHash = val2 % mod;
        }
        s++;
    }

    i = 0;
    while (i < idxCount) {
        cout << idxArr[i];
        if (i + 1 < idxCount) cout << " ";
        i++;
    }

    return 0;
}
