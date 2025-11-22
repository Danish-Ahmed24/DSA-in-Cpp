#include<iostream>
#include<map>
#include<unordered_map>
using namespace std;

int main()
{
    unordered_map<string,int> m;
    
    pair<string,int> p1 = make_pair("monkey",1);
    m.insert(p1);

    pair<string,int> p2("banana",2);
    m.insert(p2);

    m["apple"] = 3;

    m["apple"]=4; 
    m["mango"]=5;
 
    

    // cout<<m["apple"];
    // cout<<m.size()<<endl;
    // cout<<m.count("apple")<<endl;
    // m.erase("apple");
    // cout<<m.count("apple")<<endl;
 
    
    for(auto i: m){
        cout<<i.first<<"->"<<i.second<<endl;
    }
}