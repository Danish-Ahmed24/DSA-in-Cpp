#include<iostream>
using namespace std;


bool isSafe(char maze[6][6],int sol[6][6],int n ,int x ,int y){
    return (x>=0 && y>=0 && y<n && x<n && maze[x][y]!='F'&& sol[x][y]==0);
}


bool mazeSolve(char maze[6][6],int sol[6][6],int n,int x,int y){
    if(maze[x][y]=='H'){
        sol[x][y]=1;
        return true;
    }


    if(isSafe(maze,sol,n,x,y)){
        sol[x][y]=1;

        if(mazeSolve(maze,sol,n,x,y+1)){
            return true;
        }
        if(mazeSolve(maze,sol,n,x+1,y)){
            return true;
        }
        if(mazeSolve(maze,sol,n,x-1,y)){
            return true;
        }
        if(mazeSolve(maze,sol,n,x,y-1)){
            return true;
        }

        sol[x][y]=0;
        return false;
    }
    return false;
}
void printSol(int sol[6][6],int N) {
    cout << "\nPath (1 = drone path):\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << sol[i][j] << " ";
        }
        cout << endl;
    }}
int main(){
    int n =6;
    char maze[6][6]={
        {'D','S','S','F','D','F'},
        {'S','S','S','F','S','D'},
        {'S','D','S','S','S','F'},
        {'F','S','F','S','S','F'},
        {'S','S','S','D','S','F'},
        {'S','F','S','S','S','H'}
    };
    int sol[6][6]={0};
    mazeSolve(maze,sol,n,0,0);
    printSol(sol,n);
    return 0;
}