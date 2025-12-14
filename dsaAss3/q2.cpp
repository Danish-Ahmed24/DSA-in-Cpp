#include <iostream>
#include <string>
using namespace std;

bool isIsomorphic(string s1, string s2) {
    int map1[26] = {0};
    int map2[26] = {0};

    for(int i = 0; i < s1.length(); i++) {
        int c1 = s1[i] - 'a';
        int c2 = s2[i] - 'a';

        if(map1[c1] == 0 && map2[c2] == 0) {
            map1[c1] = c2 + 1;  
            map2[c2] = c1 + 1;
        }
        else {
            if(map1[c1] != c2 + 1 || map2[c2] != c1 + 1) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    string s1 = "egg";
    string s2 = "add";

    if(isIsomorphic(s1, s2)) {
        cout << "The strings are isomorphic" << endl;
    }
    else {
        cout << "The strings are NOT isomorphic" << endl;
    }

    return 0;
}
