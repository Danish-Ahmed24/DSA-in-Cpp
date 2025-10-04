#include<iostream>
using namespace std;

int powerAB(int a, int b){
    if(b==0)
        return 1;
    return a*powerAB(a,b-1);
}

int main(){
    cout<<"2^3="<<powerAB(2,3);
    return 0;
}