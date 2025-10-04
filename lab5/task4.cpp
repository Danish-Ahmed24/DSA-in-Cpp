#include<iostream>
using namespace std;

bool isSafe(int** maze,int x ,int y ,int n){
    return (x>=0 && y>=0 && x<n && y<n && maze[x][y]==1);
}
bool ratInMaze(int** maze,int x,int y,int n,int** sol){
    if(x==(n-1) && y==(n-1)){
        sol[x][y]=1;
        return true;
    }

    if(isSafe(maze,x,y,n)){
        sol[x][y]=1;
        maze[x][y]=0;

        if(ratInMaze(maze,x+1,y,n,sol)){ //down
            return true;
        }
        if(ratInMaze(maze,x,y+1,n,sol)){ //right
            return true;
        }
        if(ratInMaze(maze,x,y-1,n,sol)){//left
            return true;
        }
        if(ratInMaze(maze,x-1,y,n,sol)){ //up
            return true;
        }
        maze[x][y]=1;
        sol[x][y]=0;
        return false;
    }
    /*
    00 01
    10 11
    */
    return false;
}

int main(){
    int n;
    cout << "Enter the size of maze: ";
    cin >> n;

    int **maze=new int*[n];
    int **sol=new int*[n];
    cout << "Enter the maze matrix (1 for path, 0 for blocked):\n";
    
    //input lo maze
    for (int i = 0; i < n;  i++)
    {
        maze[i] =new int[n];
        sol[i]= new int[n];

        for (int j  = 0; j < n; j++)
        {
            cin>>maze[i][j];
            sol[i][j]=0;
        }
        
    }
    
    if(ratInMaze(maze,0,0,n,sol)){
        cout << "Solution path:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << sol[i][j] << " ";
            }
            cout << endl;
        }
    } else {
        cout<<"No solution exits"<<endl;
    }
    for(int i =0 ; i < n ; i++){
        delete [] maze[i];
        delete [] sol[i];
    }
    delete [] maze;
    delete [] sol;
    return 0;
}