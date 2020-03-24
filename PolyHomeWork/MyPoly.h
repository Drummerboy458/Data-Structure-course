//
// Created by Lww on 2018/10/20.
//
#include <iostream>
#include <fstream>
using namespace std;
//多项式类
class MyPoly {
public:
    class Node
    {
    public:
        double data;          //存放多项式系数（整形、浮点型、）
        int index;            //存放指数
        Node* next;           //指向下一个节点
        Node(double data,int index)
        {
            this->data = data;
            this->index = index;
            next = NULL;
        }
        ~Node() //析构函数回收内存
        {
            //cout<<"删除new的节点"<<endl;
        }
    };
    Node* head;
    Node* tail;
    MyPoly()                    //无参链表构造函数
    {
        head=tail=NULL;
    }
    ~MyPoly()
    {

    }
    void print();                //打印多项式
    void output();               //输出到目标文件
    void Insert_And(double data,int index); //实现加法操作和合并同类项
    void Insert_Sub(double data,int index); //减法
    void Diff();      //实现微分操作
    void Mul(MyPoly &obj,MyPoly &last_MyPoly);  //乘法
    void Div(MyPoly &myPoly,MyPoly &myPoly_top,MyPoly &myPoly_down);    //除法 具体请看函数实现
};