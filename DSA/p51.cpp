#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    bool isSafe(vector<string> &board,int row, int n, int j){
        return true;
    }
    void nQueens(vector<string> &board,int row, int n, vector<vector<string>> &ans){

        if(n == row){
            ans.push_back({board});
            return;
        }

        for(int j=0 ; j<n ; j++){

            if(isSafe(board , row , n , j)){   
                board[row][j] = 'Q';
                nQueens(board,row+1,n,ans);
                board[row][j]='.';
            }

        }    
    }

    vector<vector<string>> solveNQueens(int n) {
        vector<string> board;
        vector<vector<string>> ans;

        nQueens(board,0,n,ans);
        return ans;
    }

};


