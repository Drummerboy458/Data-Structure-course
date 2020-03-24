//
// Created by Lww on 2018/11/25.
//
#include <iostream>
#include <iomanip>
#include "fstream"
using namespace std;
int* nums = new int[N];
int swap_times = 0;
int cmp_times = 0;
void swap(int &x,int &y)
{
    int temp = x;
    x = y;
    y = temp;
    swap_times++;
}
void get_data()
{
    ifstream fin("inputfile.txt");
    nums = new int[N];
    for(int i = 0;i < N;i++)
        nums[i] = 0;
    int num = 0;
    for(int i = 0;i < N;i++)
    {
        fin>>num;
        nums[i] = num;
    }
    fin.close();
}
void output()
{
    for(int i = 0;i < N;i++)
    {
        if(i != 0 && i % 30 == 0)
            cout<<endl;
        cout.setf(ios::left);			//左对齐
        cout<<setw(5)<<nums[i];
    }
}
void sort()
{
    for(int i = 0;i < N;i++)
    {
        for(int j = 0;j < N-1-i;j++)
        {
            if(nums[j] > nums[j+1])
            {
                cmp_times++;
                swap(nums[j],nums[j+1]);
            }
        }
    }
}
void bubble_write()
{
    ofstream out("outputfile.txt",ios::app);
    out<<"冒泡排序"<<"          "<<cmp_times<<"         "<<swap_times<<endl;
    out.close();
}
void  Bubble_Sort()
{
    get_data();
    sort();
    bubble_write();
    //output();
}