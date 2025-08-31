#include<iostream>
using namespace std;


class Student{

    string name;
    double* marks;

    public:

        Student(string name){
            this->name=name;
            this->marks=new double[3];
        }

        ~Student(){
            delete[] marks;
        }

        void setMarksAtIndex(double marks , int index){
            if(index>=0 && index<3){
                *(this->marks+index) = marks;
            }
            else{
                cout<<"cant add at index "<<index<<" choose (0-2)"<<endl;
            }
        }

        void averageScore(){
            double res=0.0;
            for (int i = 0; i < 3; i++)
            {
                res+=*(this->marks+i);
            }
            res/=3;
            cout<<"Average of Object: "<<name<<" = "<<res<<endl;
        }

};


int main()
{
    Student *std1= new Student("student 1");
    std1->setMarksAtIndex(10,0);
    std1->setMarksAtIndex(15,1);
    std1->setMarksAtIndex(20,2);

    Student std2=*std1;
    cout<<"---Average before destroying original object---"<<endl;
    std1->averageScore();
    std2.averageScore();
    cout << "--- Deleting original object ---" << endl;
    delete std1;
    cout<<"---Average after destroying original object---"<<endl;
    std2.averageScore();
    
    return 0;
}

