#include<iostream>
using namespace std;

class Flight{
    string *name;
    int *seat_number;

    public:
        Flight(string name,int seat_number){
            this->name = new string;
            this->seat_number = new int;
            *(this->name)=name;
            *(this->seat_number) = seat_number;

        }
        Flight(const Flight &other){
            this->name = new string;
            this->seat_number = new int;
            *(this->name) = *(other).name;
            *(this->seat_number)= *(other).seat_number;
        }
        ~Flight(){
            delete name;
            delete seat_number;
        }
        void setName(string name){
            *(this->name) = name;
        }

        void display(){
            cout<<"Name: "<<*name<<endl;
            cout<<"Seat Number"<<*seat_number<<endl;
        }
};

int main()
{
    Flight book1("book1",1);
    //data
    Flight book2 = book1;
    book2.setName("book2");
    cout<<"--BOOK 1--"<<endl;
    book1.display();
    cout<<"--BOOK 2--"<<endl;
    book2.display();

    return 0;
}