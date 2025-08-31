#include<iostream>
using namespace std;

class BankAccount{
    double* balance;
    public:
        BankAccount(){
            balance = new double(0.0);
        }
        ~BankAccount(){
            delete balance;
        }
        BankAccount(const BankAccount& other){
            balance = new double;
            *balance = *(other.balance);
        }
        void setBalance(double balance){
            *(this->balance)=balance;
        }
        double getBalance(){
            return *(this->balance);
        }
        void withdraw(double amount){
            *(this->balance)-=amount;
        }
};

int main()
{
    BankAccount acc1;
    acc1.setBalance(10);
    BankAccount acc2 = acc1;
    acc1.withdraw(5);

    cout << "acc1 balance: " << acc1.getBalance() << endl;  
    cout << "acc2 balance: " << acc2.getBalance() << endl; 
    return 0;
}