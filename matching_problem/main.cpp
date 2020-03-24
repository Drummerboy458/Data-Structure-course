//
//  main.cpp
//  matching_problem
//
//  Created by Lww on 2019/3/14.
//  Copyright © 2019 Lww. All rights reserved.

#include <iostream>
using namespace std;
int account = 0;
int** man;
int** woman;
int** invert_matrix;
int*  bool_matrix;//woman单身判断矩阵
int*  bool_man;
void input_data(int** p)
{
    for(int i = 0;i < account;i++)
    {
        for(int j = 0;j < account;j++)
        {
            cin>>p[i][j];
        }
    }
}
void initialize()
{
    cin>>account;
    man = new int*[account];
    for(int i = 0;i < account;i++)
    {
        man[i] = new int [account];
    }
    woman = new int*[account];
    for(int i = 0;i < account;i++)
    {
        woman[i] = new int [account];
    }
    invert_matrix = new int*[account];
    for(int i = 0;i < account;i++)
    {
        invert_matrix[i] = new int [account];
    }
    bool_matrix = new int[account];
    for(int i = 0;i < account;i++)
    {
        bool_matrix[i] = -1; //初始化为-1，表示woman[i]为自由状态
    }
    bool_man = new int[account];
    for(int i = 0;i < account;i++)
    {
        bool_man[i] = -1; //初始化为-1，表示man[i]为自由状态
    }
    input_data(man);
    input_data(woman);
}
void invert(int** p,int** target)
{
    int temp = 0;
    for(int i = 0;i < account;i++)
    {
        for(int j = 0;j < account;j++)
        {
            temp = p[i][j];
            target[i][temp-1] = j+1;
        }
    }
}
//G-S算法
bool is_end()
{
    for(int i = 0;i < account;i++)
    {
        if(bool_matrix[i] == -1)
            return false;
    }
    return true;
}
int main(int argc, const char * argv[])
{
    initialize();
    invert(woman,invert_matrix);
    int j = 0;
    while(!is_end())
    {
        for(int i = 0;i < account;i++)  //从m1---m5，依次对女性发起邀请
        {
            if(bool_man[i] == -1)    //如果该男性自由
                //选中男性后，对男性的选择列表中的女性发起邀请
            {

                int temp = man[i][j]-1;   //temp为选择对象
                if(bool_matrix[temp] == -1)  //该女性自由
                {

                    bool_matrix[temp] = i;
                    bool_man[i] = temp+1;
                }
                else if(invert_matrix[temp][i] < invert_matrix[temp] [bool_matrix[temp]])   //w更喜欢m'than m
                {
                    bool_man[bool_matrix[temp]] = -1;   //恢复之前那位男性自由的身份
                    bool_matrix[temp] = i;
                    bool_man[i] = temp+1;
                }
                else    //拒绝，进入下一轮选择
                {
                    continue;
                }
            }
        }
        j++;
    }
    for(int i = 0;i < account;i++)
    {
        cout<<bool_man[i]<<" ";
    }
    cout<<endl;
}
