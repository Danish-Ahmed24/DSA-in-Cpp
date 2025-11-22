#include<iostream>
#include<string.h>
using namespace std;
class twoDarray{
    int ncols;
    int nrows;
    int *dynamicarray;
    public:
        twoDarray(){
            nrows=0;
            ncols=0;
            dynamicarray=NULL;
        }
        twoDarray(int row, int col){
            nrows=row;
            ncols=col;
            int size=ncols*nrows;
            dynamicarray=new int[size];
        }
        ~twoDarray(){
            delete [] dynamicarray;
            dynamicarray=NULL;
        }
        void insert(){
            int size=nrows*ncols;
            int i;
            for(i=0;i<size;i++){
                int value;
                cout << "enter value;" << endl;
                cin>> value;
                dynamicarray[i]=value;
            }
        }
        int &operator ()(int i,int j){
            if(i<0 || i>nrows-1 || j<0 || j>ncols-1){
                cout <<"Array Index Out of Bound" << endl;
                exit(1);
            }
            long offset=(i*ncols)+j;
            return dynamicarray[offset];
        }
        
        twoDarray(const twoDarray& ob){
            nrows=ob.nrows;
            ncols=ob.ncols;
            int size=nrows*ncols;
            dynamicarray=new int[size];
            memcpy(dynamicarray,ob.dynamicarray,sizeof(int)*nrows*ncols);
        }
        twoDarray &operator =(const twoDarray &ob1){
            if(this==&ob1)
                return *this;
            delete [] dynamicarray;
            nrows=ob1.nrows;
            ncols=ob1.ncols;
            int size=nrows*ncols;
            dynamicarray=new int[size];
            memcpy(dynamicarray,ob1.dynamicarray,sizeof(int)*nrows*ncols);
            return *this;
        }
};
int main(){
    int columns, rows;
    cout <<"enter number of rows and columns" << endl;
    cin>> rows >> columns;
    twoDarray obj1(rows,columns);
    obj1.insert();
    cout << endl << "___________" << endl;
    twoDarray obj2=obj1;
    twoDarray obj3(2,2);
    obj3.insert();
    cout << obj1(1,1) << endl;
    cout << obj3(3,1) << endl;
    return 0;
}