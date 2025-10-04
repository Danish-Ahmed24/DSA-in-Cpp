#include<iostream>
using namespace std;

int sumDigits(int n){
    if(n == 0)
        return n;

    return n%10 + sumDigits(n/10); 

}


int main(){
    int x = sumDigits(987);
    cout<<x;
    return 0;
}