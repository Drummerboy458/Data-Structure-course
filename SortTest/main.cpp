#include <iostream>
#include <iomanip>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include "SelectSort.h"
#include "BubbleSort.h"
#include "InsertSort.h"
#include "QuickSort.h"
#include "Shell.h"
using namespace std;
void generate_number()
{
    ofstream out("inputfile.txt");
    srand((unsigned) time(NULL));   //种子
    for(int i = 0;i < N;i++)
    {
        if(i != 0 && i % 30 == 0)
            out<<endl;
        int num = rand()% N;
        out.setf(ios::left);			//左对齐
        out<<setw(5)<<num;
    }
    out.close();

    ofstream out1("outputfile.txt",ios::app);
    out.setf(ios::left);			//左对齐
    out<<setw(5);
    out1<<"排序算法"<<"         "<<"比较次数"<<"            "<<"交换次数"<<endl;
    out1.close();
}
int main()
{
    generate_number();  //生成排序测试数据
    Bubble_Sort();
    Select_Sort();
    Quick_Sort();
    Insert_Sort();
   Shell_Sort();
}