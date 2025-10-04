#include <iostream>
using namespace std;

bool isPalindrome(string str, int x, int y)
{
    if (x >= y)
        return true;
    if (str[x] != str[y])
        return false;
    return isPalindrome(str, x + 1, y - 1);
}

int main()
{
    string str2 = "hello";
    string str1 = "racecar";
    cout << str1 << " "
         << (isPalindrome(str1, 0, str1.length() - 1) ? "is palindrome" : "not palindrome")
         << endl;
    cout << str2 << " "
         << (isPalindrome(str2, 0, str2.length() - 1) ? "is palindrome" : "not palindrome");
    return 0;
}