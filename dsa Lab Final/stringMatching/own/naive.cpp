#include<iostream>
using namespace std;

void naive(string pattern , string text){
    int m = text.size();
    int n = pattern.size();

    for(int i=0 ; i <=m-n ; i++){
        int j =0;
        while(j<n && text[i+j]==pattern[j]){
            j++;
        }
        if(j==n){
            cout<<"FOund at "<<i;
        }
    }
}

int main()
{
        
}