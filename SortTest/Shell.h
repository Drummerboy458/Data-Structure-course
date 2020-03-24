//
// Created by Lww on 2018/11/25.
//
//
// Created by Lww on 2018/11/25.
//
#include <iostream>
#include "fstream"
using namespace std;
int* shell_nums = new int[N];
int shell_swap_times = 0;
int shell_cmp_times = 0;
void shell_swap(int &x,int &y)
{
    int temp = x;
    x = y;
    y = temp;
    shell_swap_times++;
}
void shell_get_data()
{
    ifstream fin("inputfile.txt");
    shell_nums = new int[N];
    for(int i = 0;i < N;i++)
        shell_nums[i] = 0;
    int num = 0;
    for(int i = 0;i < N;i++)
    {
        fin>>num;
        shell_nums[i] = num;
    }
    fin.close();
}
void shell_output()
{
    for(int i = 0;i < N;i++)
    {
        if(i != 0 && i % 30 == 0)
            cout<<endl;
        cout.setf(ios::left);			//左对齐
        cout<<setw(5)<<shell_nums[i];
    }
}
void shell_sort()
{
    for(int step = N/2;step > 0;step /= 2)
    {
        for(int i = 0;i < N;i++)
        {
            while (i- step >= 0 && shell_nums[i - step] > shell_nums[i])
            {
                shell_cmp_times++;
                shell_swap(shell_nums[i-step],shell_nums[i]);
            }
        }
    }
}
void shell_write()
{
    ofstream out("outputfile.txt",ios::app);
    out<<"希尔排序"<<"          "<<shell_cmp_times<<"           "<<shell_swap_times<<endl;
    out.close();
}
void  Shell_Sort()
{
    shell_get_data();
    shell_sort();
    shell_write();
    shell_output();
}
