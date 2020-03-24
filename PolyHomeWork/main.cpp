#include <iostream>
#include <string>
#include "MyPoly.h"
using namespace std;
/*
 * 主函数实现两个多项式的的读取、初始化
 * 调用Poly函数、加、减、乘、除、微分、功能函数
 */
int main()
{
    /*
     * myPoly1为多项式一
     * mypoly2为多项式二
     * mypoly3为结果多项式,用于存放乘或除之后的结果
     */
        MyPoly myPoly1;
        MyPoly myPoly2;
        MyPoly myPoly3;
        int data = 0;   //系数
        int index = 0;  //指数

        /*定义三个字符串，string1为读入的多项式一;string2为读入的多项式二；calculate为读入的操作
         * 字符串AND,SUB,MUL,DIFF,DIV匹配读入到的字符串，以调用不同的函数
         */
        string string1,string2,calculate;
        string AND = "AND(#,#)";
        string SUB = "SUB(#,#)";
        string MUL = "MUL(#,#)";
        string DIFF = "DIFF(#,#)";
        string DIV = "DIV(#,#)";

        ifstream infile("inputfile.txt");           //开始对"inputfile.txt"的读取
        infile>> string1 >> string2 >>calculate;    //读出两个多项式
        infile.close();

        /*
         * i 判断是否到字符串末尾
         * x 存放每次读取到的字符
         * 以解析字符串的方式读取系数和和指数
         */
        int i = 0;
        char x;
        while(i < string1.length())
        {
            x  = string1[i];
            if(x == '(')
            {
                //下一个数为多项式的系数
                i++;
                x = string1[i];  //读第一个数
                string str_data="";     //系数
                while(x != ',')
                {
                    str_data = str_data + x;
                    i++;
                    x = string1[i];
                }
                data = atoi(str_data.c_str());      //调用atoi()函数将取到的非特殊字符转换成int型 得到该项的系数
                //下一步读取指数index
                i++;
                x = string1[i];   //读指数
                string str_index="";       //指数
                while(x != ')')
                {
                    str_index = str_index + x;
                    i++;
                    x = string1[i];
                }
                index = atoi(str_index.c_str());        //得到该项的指数
                //cout<<data<<" "<<index<<endl;
                if(data != 0)
                {
                    myPoly1.Insert_And(data, index);    //先判断是否为有效项，再插入到多项式一
                }
            }
            else
                i++;
        }
        i = 0;
        while(i < string2.length())         //对多项式二进行有效读取，同多项式一
        {
            x  = string2[i];
            if(x == '(')
            {
                //下一个数为多项式的系数
                i++;
                x = string2[i];  //读第一个数
                string str_data="";     //系数
                while(x != ',')
                {
                    str_data = str_data + x;
                    i++;
                    x = string2[i];
                }
                data = atoi(str_data.c_str());      //转换成int型 得到该项的系数
                //下一步读取指数index
                i++;
                x = string2[i];   //读指数
                string str_index="";       //指数
                while(x != ')')
                {
                    str_index = str_index + x;
                    i++;
                    x = string2[i];
                }
                index = atoi(str_index.c_str());        //得到该项的指数
                //cout<<data<<" "<<index<<endl;
                if(data != 0)
                {
                    myPoly2.Insert_And(data, index);
                }
            }
            else
                i++;
        }
        cout<<"多项式一:";      //控制台打印到控制台
        myPoly1.print();
        cout<<"多项式二:";
        myPoly2.print();
        cout<<"要进行的操作是:"<<calculate<<endl;
        if(calculate == AND)    //以下为匹配相应文件要求的操作
        {
            MyPoly::Node* temp = myPoly2.head;
            while(temp != NULL)
            {
                myPoly1.Insert_And(temp->data, temp->index);
                temp = temp->next;
            }
            cout<<"多项式一与多项式二的和:";
            myPoly1.print();
            myPoly1.output();   //将结果输出到目标文件
        }
        if(calculate == SUB)
        {
            MyPoly::Node* temp = myPoly2.head;
            while(temp != NULL)
            {
                myPoly1.Insert_Sub(temp->data, temp->index);
                temp = temp->next;
            }
            cout<<"多项式一减多项式二结果:";
            myPoly1.print();
            myPoly1.output();
        }
        if(calculate == DIFF)
        {
            myPoly1.Diff();
            cout<<"多项式一微分后:";
            myPoly1.print();
            myPoly1.output();

            myPoly2.Diff();
            cout<<"多项式二微分后:";
            myPoly2.print();
            myPoly2.output();
        }
        if(calculate == MUL)
        {
            cout<<"多项式一与多项式二的乘积:";
            myPoly1.Mul(myPoly2, myPoly3);
            myPoly3.print();
            myPoly3.output();
        }
        if(calculate == DIV)
        {
            myPoly1.Div(myPoly1, myPoly2, myPoly3);
        }
}