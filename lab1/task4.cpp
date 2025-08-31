#include <iostream>
using namespace std;

int main()
{
    int len = 0;
    string a;

    cout << "Enter first word: ";
    cin >> a;
    len += a.length() + 1;
    char* word1 = new char[a.length() + 1];
    for (int i = 0; i < (int)a.length(); i++) {
        word1[i] = a[i];
    }
    word1[a.length()] = '\0';  

    cout << "Enter second word: ";
    cin >> a;
    len += a.length() + 1;  
    char* word2 = new char[a.length() + 1];
    for (int i = 0; i < (int)a.length(); i++) {
        word2[i] = a[i];
    }
    word2[a.length()] = '\0';  

    len++; 

    char* concatenated_res = new char[len];
    
    int pos = 0;

    for (int i = 0; word1[i] != '\0'; i++) {
        concatenated_res[pos++] = word1[i];
    }

    concatenated_res[pos++] = ' ';

    for (int i = 0; word2[i] != '\0'; i++) {
        concatenated_res[pos++] = word2[i];
    }

    concatenated_res[pos] = '\0';

    cout << "Concatenated result: " << concatenated_res << endl;

    // freeing
    delete[] word1;
    delete[] word2;
    delete[] concatenated_res;

    return 0;
}
