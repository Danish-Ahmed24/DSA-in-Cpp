#include<iostream>
using namespace std;

int main()
{
    int len = 0 ;
    cout<<"Enter length of your name: ";
    cin>> len;
    char* name = new char[len+1];
    cout<<"Enter your name: ";
    cin>>name;

    cout<<"\n---Displaying name char by char---\n"<<endl;
    for (int i = 0; i < len; i++)
    {
        cout<<*(name+i);
    }
    
    // freeing
    delete name;
    
    return 0;
}