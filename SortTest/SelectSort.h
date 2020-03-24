//
// Created by Lww on 2018/11/25.
//
#include <iostream>
#include "fstream"
using namespace std;
const int N = 10000;
int* select_nums = new int[N];
int select_swap_times = 0;
int select_cmp_times = 0;
void select_swap(int &x,int &y)
{
    int temp = x;
    x = y;
    y = temp;
    select_swap_times++;
}
void select_get_data()
{
    ifstream fin("inputfile.txt");
    select_nums = new int[N];
    for(int i = 0;i < N;i++)
        select_nums[i] = 0;
    int num = 0;
    for(int i = 0;i < N;i++)
    {
        fin>>num;
        select_nums[i] = num;
    }
    fin.close();
}
void select_output()
{
    for(int i = 0;i < N;i++)
    {
        if(i != 0 && i % 30 == 0)
            cout<<endl;
        cout.setf(ios::left);			//左对齐
        cout<<setw(5)<<select_nums[i];
    }
}
void select_sort()
{
    for(int i = 0;i < N;i++)    //从小到大,i为每次选出的最小数
    {
       int min_index = i;
       for(int j = i+1;j < N;j++)
       {
           if(select_nums[min_index] > select_nums[j])
           {
               select_cmp_times++;
               min_index = j;
           }
       }
        if(min_index != i)
        {
            select_cmp_times++;
            select_swap(select_nums[min_index],select_nums[i]);
        }
    }
}
void select_write()
{
    ofstream out("outputfile.txt",ios::app);
    out<<"选择排序"<<"          "<<select_cmp_times<<"              "<<select_swap_times<<endl;
    out.close();
}
void  Select_Sort()
{
    select_get_data();
    select_sort();
    select_write();
    //select_output();
}