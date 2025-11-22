#include<iostream>
using namespace std;

class A{
    public:
    int ncols;
    int *arr;
    
    A(){
        ncols=0;
        arr = NULL;
    }
    A(int ncols){
        this->ncols=ncols;
        arr = new int[ncols];
    }
    ~A(){
        delete [] arr;
        arr = NULL;
    }

    A(const A &ob){
        this->ncols=ob.ncols;
        arr = new int[ncols];

        for(int i =0 ; i < ncols ; i++){
            arr[i] = ob.arr[i];
        }
    }

    A& operator =(const A& ob){
        if (this == &ob){
            return *this;
        }

        delete [] arr;
        
        ncols = ob.ncols;
              for (int i = 0; i < ncols; i++) {
            arr[i] = ob.arr[i];
        }
        return *this;
    }
    int& operator[](int i){
        if(i<0 || i>ncols){
            cout<<"np";
            exit(1);
        }
        return arr[i];
    }


    void insert(){
            int i;
            for(i=0;i<ncols;i++){
                int value;
                cout << "enter value";
                cin >> value;
                arr[i]=value;
            }
        }
        void display(){
            int i;
            for(i=0;i<ncols;i++){
                cout << arr[i] << " ";
            }
            cout<<endl;
        }
    
}; 
 
int main()
{
    A a(2);
    a.insert();
    a.display();
    A b(2);
    b.insert();
    b.display();

    a = b;
    cout<<"----------SHALLDO----------"<<endl;
    b.insert();
    a.display();

    a.arr[-1]=3;
    a.arr[2]=33;
    a.display();

}