#include<iostream>
using namespace std;


int factorialTail(int n , int result=1){
    if(n==0 || n==1)
        return result;

    return factorialTail(n-1,n*result);
}

int factorialNonTail(int n){
    if(n==0 || n==1)
        return 1;
    return n * factorialNonTail(n-1);
}


int main(){
    int resT = factorialTail(6);
    int resNT = factorialNonTail(6);
    cout<<"by tail recursion: "<<resT<<endl<<"by non tail recursion: "<<resNT;
    return 0;
}