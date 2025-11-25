#include <iostream>
using namespace std;

int strLen(const char s[]) {
    int i = 0;
    while (s[i] != '\0') i++;
    return i;
}

void strCopy(char dest[], const char src[]) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

int strCmp(const char a[], const char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] < b[i]) return -1;
        if (a[i] > b[i]) return 1;
        i++;
    }
    if (a[i] == '\0' && b[i] == '\0') return 0;
    if (a[i] == '\0') return -1;
    return 1;
}

int hashName(const char s[]) {
    long long h = 0;
    int i = 0;
    while (s[i] != '\0') {
        h = h * 31 + (unsigned char)s[i];
        if (h < 0) h = -h;
        i++;
    }
    return (int)(h % 101);
}

class NameNode {
public:
    char name[50];
    int index;
    NameNode* next;
    NameNode(const char n[], int idx) {
        strCopy(name, n);
        index = idx;
        next = 0;
    }
};

int findOrInsertName(NameNode* table[], const char name[], char names[][50], int &nameCount) {
    int h = hashName(name);
    NameNode* cur = table[h];
    while (cur != 0) {
        if (strCmp(cur->name, name) == 0) return cur->index;
        cur = cur->next;
    }
    int idx = nameCount;
    strCopy(names[idx], name);
    nameCount++;
    NameNode* n = new NameNode(name, idx);
    n->next = table[h];
    table[h] = n;
    return idx;
}

int main() {
    int n;
    cin >> n;

    const int MAXN = 200;
    char emp[MAXN][50];
    char man[MAXN][50];

    int i = 0;
    while (i < n) {
        cin >> emp[i] >> man[i];
        i++;
    }

    NameNode* hashTable[101];
    i = 0;
    while (i < 101) {
        hashTable[i] = 0;
        i++;
    }

    char names[MAXN * 2][50];
    int nameCount = 0;

    i = 0;
    while (i < n) {
        findOrInsertName(hashTable, emp[i], names, nameCount);
        findOrInsertName(hashTable, man[i], names, nameCount);
        i++;
    }

    int mgr[MAXN * 2];
    int adj[MAXN * 2][MAXN * 2];
    int adjSize[MAXN * 2];

    i = 0;
    while (i < nameCount) {
        adjSize[i] = 0;
        mgr[i] = -1;
        i++;
    }

    i = 0;
    while (i < n) {
        int eIdx = findOrInsertName(hashTable, emp[i], names, nameCount);
        int mIdx = findOrInsertName(hashTable, man[i], names, nameCount);
        mgr[eIdx] = mIdx;
        int k = adjSize[mIdx];
        adj[mIdx][k] = eIdx;
        adjSize[mIdx] = k + 1;
        i++;
    }

    int ceo = -1;
    i = 0;
    while (i < nameCount) {
        if (mgr[i] == i) {
            ceo = i;
            break;
        }
        i++;
    }

    int visited[MAXN * 2];
    int countSub[MAXN * 2];
    i = 0;
    while (i < nameCount) {
        visited[i] = 0;
        countSub[i] = 0;
        i++;
    }

    int stackNodes[MAXN * 2];
    int stackState[MAXN * 2];

    int stackTop = -1;
    stackTop++;
    stackNodes[stackTop] = ceo;
    stackState[stackTop] = 0;

    while (stackTop >= 0) {
        int node = stackNodes[stackTop];
        int state = stackState[stackTop];

        if (state == 0) {
            visited[node] = 1;
            stackState[stackTop] = 1;
            int j = 0;
            while (j < adjSize[node]) {
                int child = adj[node][j];
                if (!visited[child]) {
                    stackTop++;
                    stackNodes[stackTop] = child;
                    stackState[stackTop] = 0;
                }
                j++;
            }
        } else {
            int total = 0;
            int j = 0;
            while (j < adjSize[node]) {
                int child = adj[node][j];
                total += 1 + countSub[child];
                j++;
            }
            countSub[node] = total;
            stackTop--;
        }
    }

    int idxList[MAXN * 2];
    i = 0;
    while (i < nameCount) {
        idxList[i] = i;
        i++;
    }

    int a = 0;
    while (a < nameCount - 1) {
        int b = a + 1;
        while (b < nameCount) {
            if (strCmp(names[idxList[a]], names[idxList[b]]) > 0) {
                int tmp = idxList[a];
                idxList[a] = idxList[b];
                idxList[b] = tmp;
            }
            b++;
        }
        a++;
    }

    i = 0;
    while (i < nameCount) {
        int idx = idxList[i];
        cout << names[idx] << " " << countSub[idx] << '\n';
        i++;
    }

    i = 0;
    while (i < 101) {
        NameNode* cur = hashTable[i];
        while (cur != 0) {
            NameNode* del = cur;
            cur = cur->next;
            delete del;
        }
        i++;
    }

    return 0;
}
