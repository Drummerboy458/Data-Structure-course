//
// Created by Lww on 2018/11/25.
//

//
// Created by Lww on 2018/11/25.
//
#include <iostream>
#include "fstream"
using namespace std;
int* quick_nums = new int[N];
int quick_swap_times = 0;
int quick_cmp_times = 0;
void quick_swap(int &x,int &y)
{
    int temp = x;
    x = y;
    y = temp;
    quick_swap_times++;
}
void quick_get_data()
{
    ifstream fin("inputfile.txt");
    quick_nums = new int[N];
    for(int i = 0;i < N;i++)
        quick_nums[i] = 0;
    int num = 0;
    for(int i = 0;i < N;i++)
    {
        fin>>num;
        quick_nums[i] = num;
    }
    fin.close();
}
void quick_output()
{
    for(int i = 0;i < N;i++)
    {
        if(i != 0 && i % 30 == 0)
            cout<<endl;
        cout.setf(ios::left);			//左对齐
        cout<<setw(5)<<quick_nums[i];
    }
}
void quick_sort(int* nums,int l,int r)  //nums[l:r},l为支撑点
{
    if(l >= r)  //该片段排序完成
    {
        return;
    }
    int i = l;  //从左到右的游标
    int j = r+1;
    int pivot = quick_nums[l];  //将顶点设置为nums[l]
    while(true)
    {
        do {
            i = i + 1;
            quick_cmp_times++;
        } while (quick_nums[i] < pivot);
        do {
            quick_cmp_times++;
            j = j - 1;
        } while (quick_nums[j] > pivot);
        if(i >= j)  //碰头
        {
            break;
        }
        quick_swap(quick_nums[i],quick_nums[j]);   //交换
    }
    quick_nums[l] = quick_nums[j];
    quick_nums[j] = pivot;  //将顶点置于正确的位置 如 4 (2 3 (j)1) ((i)7 5 6 8) 将4与1交换

    quick_sort(quick_nums,l,j-1);   //对左段排序
    quick_sort(quick_nums,j+1,r);   //对右端排序
}
void quick_write()
{
    ofstream out("outputfile.txt",ios::app);
    out<<"快速排序"<<"          "<<quick_cmp_times<<"           "<<quick_swap_times<<endl;
    out.close();
}
void  Quick_Sort()
{
    quick_get_data();
    quick_sort(quick_nums,0,N-1);
    quick_write();
    //quick_output();
}