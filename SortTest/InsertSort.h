//
// Created by Lww on 2018/11/25.
//
#include <iostream>
#include "fstream"
using namespace std;
int* insert_nums = new int[N];
int insert_swap_times = 0;
int insert_cmp_times = 0;
void insert_swap(int &x,int &y)
{
    int temp = x;
    x = y;
    y = temp;
    insert_swap_times++;
}
void insert_get_data()
{
    ifstream fin("inputfile.txt");
    insert_nums = new int[N];
    for(int i = 0;i < N;i++)
        insert_nums[i] = 0;
    int num = 0;
    for(int i = 0;i < N;i++)
    {
        fin>>num;
        insert_nums[i] = num;
    }
    fin.close();
}
void insert_output()
{
    for(int i = 0;i < N;i++)
    {
        if(i != 0 && i % 30 == 0)
            cout<<endl;
        cout.setf(ios::left);			//左对齐
        cout<<setw(5)<<insert_nums[i];
    }
}
void insert_sort()
{
    for(int i = 1;i < N;i++)    //初始从index=1
    {
        for(int j = i;j >= 1 && insert_nums[j] < insert_nums[j-1];j--)
        {
            insert_cmp_times++;
            insert_swap(insert_nums[j],insert_nums[j-1]);
        }
    }
}
void insert_write()
{
    ofstream out("outputfile.txt",ios::app);
    out<<"插入排序"<<"          "<<insert_cmp_times<<"          "<<insert_swap_times<<endl;
    out.close();
}
void  Insert_Sort()
{
    insert_get_data();
    insert_sort();
    insert_write();
    //cout<<"insert_cmp_times:"<<insert_cmp_times<<endl;
    //insert_output();
}