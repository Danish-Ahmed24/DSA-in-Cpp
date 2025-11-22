#include<iostream>
#include<string.h>

using namespace std;

class oneDarray{
    int ncols;
    int *dynamic_array;
    public:
        oneDarray(){
            ncols=0;
            dynamic_array=NULL;
        }
        oneDarray(int col){
            ncols=col;
            dynamic_array=new int[ncols];
        }
        ~oneDarray(){
            delete [] dynamic_array;
            dynamic_array=NULL;
        }
        void insert(){
            int i;
            for(i=0;i<ncols;i++){
                int value;
                cout << "enter value" << endl;
                cin >> value;
                dynamic_array[i]=value;
            }
        }
        void display(){
            int i;
            for(i=0;i<ncols;i++){
                cout << dynamic_array[i] << endl;
            }
        }
        int &operator [](int i){
            if(i<0 || i>ncols-1){
                cout <<"Array Index Out of Bound" << endl;
                exit(1);
            }
            return dynamic_array[i];
        }
        oneDarray(const oneDarray& obj){
            ncols=obj.ncols;
            dynamic_array=new int[ncols];
            //memcpy(dynamic_array,obj.dynamic_array,sizeof(int)*ncols);
            //you can also use for loop to copy the contents
            for(int i = 0; i < ncols; i++)
    			dynamic_array[i] = obj.dynamic_array[i];

        }
        
        oneDarray &operator =(const oneDarray& ob){
       // self assignment check if obj1=obj1;
            if(this==&ob)
                return *this;
   			// delete already assigned memory of the object    
            delete [] dynamic_array;
            dynamic_array=NULL;
            
            //and then copy the code of copy constructor.
            ncols=ob.ncols;
            dynamic_array=new int [ncols];
            memcpy(dynamic_array, ob.dynamic_array, sizeof(int)*ncols);
            return *this;
        }

};


int main(){
    int columns, columns1;
    cout <<" Enter number of Columns" << endl;
    cin >> columns;
    oneDarray obj1(columns);
    obj1.insert();
    obj1.display();
    cout <<" Enter number of Columns for new object" << endl;
    cin >> columns1;
    oneDarray obj3(columns1);
    obj3.insert();
    obj3.display();
    //
    obj3=obj1;
    obj3.display();
    cout<< "change the values of obj1" << endl;
    obj1.insert();
    obj3.display();
    
}
