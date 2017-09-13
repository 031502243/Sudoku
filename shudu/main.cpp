#include<iostream>
#include<ctime>
#include<fstream>
#include <stdlib.h>
#include <stdio.h>
#define N (4+3)%9+1 

using namespace std;

int sudoku[9][9];
ofstream fout;

void initSudoku(){
    for(int i = 0 ; i < 9 ; i++){
        for (int j = 0 ; j < 9 ; j++){
            sudoku[i][j] = 0;
        }
    }
    sudoku[0][0] = N ;//将sudoku[0][0]设置为题目要求
}

bool Judge(int x, int y, int val)
{
    if(sudoku[y][x] != 0)//非空
        return false;
    int x0, y0;
//    for(x0 = 0;x0<9;x0++)
//    {
//        if (sudo[y][x0] == val)//行冲突
//            return false;
//    }
    for (y0 = 0; y0<9; y0++)
    {
        if (sudoku[y0][x] == val)//列冲突
            return false;
    }
    for(y0 = y / 3 * 3 ; y0<y / 3 * 3 + 3 ; y0++)
    {
        for(x0 = x / 3 * 3 ; x0 < x / 3 * 3 + 3 ; x0++)
        {
            if(sudoku[y0][x0] == val)//格冲突
                return false;
        }
    }
    sudoku[y][x] = val;
    return true;
}

void reset(int x, int y)
{
    sudoku[y][x] = 0;
}



bool set(int y, int val)
{
    int xOrd[9] ;
    
    int i, k, tmp;
    for(i=0;i<9;i++)
    {
        xOrd[i] = i;
    }
    for(i = 0;i<9;i++) //生成当前行的扫描序列，实现随机填入位置
    {
        k = rand() % 9;
        tmp = xOrd[k];
        xOrd[k] = xOrd[i];
        xOrd[i] = tmp;
    }

    for (int i = 0 ; i < 9 ; i++)
    {
        int x = xOrd[i];
        
        if (val == N && x == 0 && y == 0)//判断是不是第一行第一列的位置
        {
            if(set(y + 1,val))//下一行继续填当前数
                return true;
        }
        
        if (Judge(x, y, val))
        {
            if (y == 8)//最后一行
            {
                if (val == 9 || set(0, val + 1))
                    return true;
            }
            else
            {
                if(set(y + 1,val))//下一行继续填当前数
                    return true;
            }
            reset(x, y);//回溯
        }
    }
    return false;
}

void printSudoku()
{
    for (int y = 0;y<9;y++)
    {
        for(int x = 0;x<9;x++)
        {
            cout<< sudoku[y][x] << " ";
            fout<< sudoku[y][x] << " ";
        }
        cout<< endl;
        fout<< endl;
    }
    cout << endl;
    fout << endl;
   
}



int main(int argc, char* argv[])
{
    srand((unsigned)time(NULL));
    fout.open("sudoku.txt");
    int num;
        if ( argc != 3) {
            printf("Usage: sudoku.exe -c [N:a number]\n");
            return 0;
        }
        if (argc == 3)
        {
            num=atoi(argv[2]);
            
            if (num == 0) {
                printf("Please enter a number greater than 1!\n");
                return 0;
            }
            else{
//            while (!(cin >> n)) {
//                cin.clear();
//                // reset input
//                while (cin.get() != '\n')
//                    continue;
//                // get rid of bad input
//                cout << "Please enter a number: ";
//            }
            while(num--)
            {
                initSudoku(); //每次循环都要初始化数独数组
                while (!set(0, 1));
                printSudoku();
//          cout << endl;
            }
        }
    }
     fout.close();
//    cout<< "1";
    return 0;
}
