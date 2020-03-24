//
// Created by Lww on 2018/10/21.
//
#include "MyPoly.h"
/*
 * 具体实现MyPoly成员函数功能
 * print函数负责输出到控制台调试
 * 以及负责输出目标多项式和目标值到文件中
 */
void MyPoly:: print()                //打印
{
    Node* temp = head;
    if(temp->data == 0 && temp->next != NULL )
    {
        temp = temp->next;      //首项系数如果为0 则不输出
    }
    else if(temp->data == 0 && temp->next == NULL)  //只有一项
    {
        cout<<"0";
        return;
    }
    while(temp->next != NULL)   //该项不是最后一项时
    {

        if(temp->data != 0)
        {
            if(temp->index == 0) //常数项
            {
                if(temp->next->data == 0)      //下一项如果系数为0
                {
                    cout<<temp->data;
                }
                else if(temp->next->data > 0)
                {
                    cout<<temp->data<<"+";
                }
                else if(temp->next->data < 0)
                {
                    cout<<temp->data;
                }

            }
            else                //一般项 该项指数不为0
            {
                if(temp->next->data <= 0)      //下一项如果系数为0
                {
                    cout<<temp->data<<"X"<<temp->index;
                }
                else                             //为正数
                {
                    cout<<temp->data<<"X"<<temp->index<<"+";
                }
            }
        }
        if(temp->data == 0 && temp->next->data > 0)
        {
            cout << "+";
        }
        temp=temp->next;        //遍历一遍
    }
    if(temp->next == NULL)      //如果该项为最后一项
    {
        if(temp->data != 0)
        {
            if(temp->index == 0)
            {
                cout<<temp->data;
            }
            else
            {
                cout<<temp->data<<"X"<<temp->index;
            }
        }
    }
    cout<<endl;
}
//输出到目标文件"outputfile.txt"
void MyPoly::output()
{
    ofstream outfile("outputfile.txt",ios::app);
    Node* temp = head;
    if(temp->data == 0 && temp->next != NULL)
    {
        temp = temp->next;      //首项系数如果为0 则不输出
    }
    else if(temp->data == 0 && temp->next == NULL)  //只有一项
    {
        outfile<<"0";
        return;
    }
    while(temp->next != NULL)   //该项不是最后一项时
    {

         if(temp->data != 0) {
             if (temp->index == 0) //常数项
             {
                 if (temp->next->data == 0)      //下一项如果系数为0
                 {
                     outfile << temp->data;
                 } else if (temp->next->data > 0) {
                     outfile << temp->data << "+";
                 } else if (temp->next->data < 0) {
                     outfile << temp->data;
                 }

             } else                //一般项 该项指数不为0
             {
                 if (temp->next->data <= 0)      //下一项如果系数为0
                 {
                     outfile << temp->data << "X" << temp->index;
                 } else                             //为正数
                 {
                     outfile << temp->data << "X" << temp->index << "+";
                 }
             }
         }
        if(temp->data == 0 && temp->next->data > 0) {
            outfile<<"+";
        }
            temp=temp->next;        //遍历一遍
    }
    if(temp->next == NULL)      //如果该项为最后一项
    {
        if(temp->data != 0)
        {
            if(temp->index == 0)
            {
                outfile<<temp->data;
            }
            else
            {
                outfile<<temp->data<<"X"<<temp->index;
            }
        }
    }
    outfile<<endl;
    outfile.close();
}
/*
 * 加法同减法一样
 * 只需考虑一些系数为0的项抛弃就行
 */
void MyPoly:: Insert_And(double data,int index)
{
    Node* current=new Node(data,index);  //实体化传入的数据为节点
    if(head == NULL)
    {
        head=tail=current;       //第一个数据
    }
    else
    {
        //与头指针比较大小
        if(index < head->index)
        {
            current->next=head;
            head=current;
            return;
        }
        else if(index == head->index)
        {
            head->data = head->data + current->data;        //和第一项指数相等  合并同类项
            if(head->data == 0)
            {
                Node* temptrr = head->next;     //释放空间
                delete head;
                head = temptrr;
            }
            return;
        }
            //与尾指针比较大小
        else if(index > tail->index)
        {
            tail->next=current;
            tail=current;
            return;
        }
        else if(index == tail->index)
        {
            tail->data = tail->data + current->data;        //和最后一项指数相等
            if(tail->data == 0)
            {
                Node *tempptr = head;          //找到尾部前一个节点
                while(tempptr->next->next!=NULL)
                {
                    tempptr=tempptr->next;
                }
                Node* temptrr = tempptr;     //释放空间
                delete tail;
                tail = temptrr;
            }
            return;
        }
            //介于头指针与尾指针之间
        else
        {
            Node* temp=head;
            while(temp->next != NULL)
            {
                if(index > temp->index && index < temp->next->index )
                {
                    current->next=temp->next;
                    temp->next=current;
                }
                else if(index > temp->index && index == temp->next->index )
                {
                    temp->next->data = temp->next->data + current->data;
                    if(temp->next->data == 0 )
                    {
                        Node *tempptr = temp->next->next;          //指向后一个节点
                        delete temp->next;
                        temp->next = tempptr;
                    }
                }
                temp=temp->next;
            }
        }
    }
}
/*
 * 减法操作不麻烦
 * 只是细节处理比较麻烦
 */
void MyPoly:: Insert_Sub(double data,int index) {
    Node* current=new Node(data,index);  //实体化传入的数据为节点
    if(head == NULL)
    {
        head=tail=current;       //第一个数据
        current->data = (- current->data);
    }
    else
    {
        //与头指针比较大小
        if(index < head->index)
        {
            current->data = (- current->data);
            current->next=head;
            head=current;
            return;
        }
        else if(index == head->index)
        {
            head->data = head->data - current->data; //和第一项指数相等  合并同类项
            if(head->data == 0 && head->next != NULL)
            {
                Node* temptrr = head->next;     //释放空间
                delete head;
                head = temptrr;
            }
            return;
        }
            //与尾指针比较大小
        else if(index > tail->index)
        {
            current->data = (- current->data);
            tail->next=current;
            tail=current;
            return;
        }
        else if(index == tail->index)               //和最后一项指数相等
        {
            tail->data = tail->data - current->data;
            if(tail->data == 0) {
                Node *tempptr = head;          //找到尾部前一个节点
                while (tempptr->next->next != NULL) {
                    tempptr = tempptr->next;
                }
                Node *temptrr = tempptr;     //释放空间
                delete tail;
                tail = temptrr;
            }
            return;
        }
            //介于头指针与尾指针之间
        else
        {
            Node* temp=head;
            while(temp->next != NULL )      //temp不是最后一项时
            {
                if(index > temp->index && index < temp->next->index ) //ww == temp ww
                {
                    current->data = (- current->data);
                    current->next=temp->next;
                    temp->next=current;
                }
                else if(index > temp->index && index == temp->next->index )
                {
                    //下一个项的指数与该项相等 ww == temp ww cc
                    temp->next->data = temp->next->data - current->data;
                    if(temp->next->data == 0)
                    {
                        if(temp->next->next != NULL)    //后面还有项
                        {
                            Node *tempptr = temp->next->next;          //指向后一个节点
                            delete temp->next;
                            temp->next = tempptr;
                        }
                        else        //后面没有项 到链表尾
                        {
                            delete  tail;
                            tail = temp;
                        }
                    }
                }
                temp=temp->next;
            }
        }
    }
}
/*
 * 微分简单
 * 系数x指数 指数减一
 */
void MyPoly::Diff(){        //实现微分操作
    Node* temp=head;
    while(temp != NULL)
    {
        if(temp->index != 0)
        {
            temp->data = temp->data * temp->index;
            temp->index -= 1;
        }
        else
            temp->data = 0;
        temp=temp->next;
    }
}
/*
 * 乘法操作就是一个二层循环的遍历
 */
void MyPoly:: Mul(MyPoly &myPoly,MyPoly &result){        //实现乘法操作 结果存到last_MyPoly
    Node* head_myPoly1 = head;
    int data = 0;   //存放乘后系数
    int index = 0;  //存放乘后指数
    while(head_myPoly1 != NULL)
    {
        Node* head_myPoly2 = myPoly.head;
        while(head_myPoly2 != NULL)
        {
            data = head_myPoly1->data * head_myPoly2->data;
            index = head_myPoly1->index + head_myPoly2->index;
            result.Insert_And(data, index);
            head_myPoly2= head_myPoly2->next;
        }
        head_myPoly1 = head_myPoly1->next;
    }
}
/*分子最高次幂项与分母最高次幂项相除得到一个值，再乘以分母（除数），得到一个temp_poly多项式
 * 再用分子（被除数）减去temp_poly，得到新的被除数（新的分子）
 * 循环操作，直到余数的最高次幂小于除数的最高次幂
 *remender为被除数，也是最后的余数
 * myPoly为除数
 *topPoly存放最后的商多项式
 */
void MyPoly:: Div(MyPoly &remender,MyPoly &myPoly,MyPoly &topPoly) {
    int MyPoly1_max_index = remender.tail->index;   //余数的最高次幂
    int MyPoly2_max_index = myPoly.tail->index;       //除数的最高次幂
    while (MyPoly1_max_index >= MyPoly2_max_index )   //当余数多项式的商大于等于除数多项式时，没除尽
    {
        MyPoly temp_top; //用于存放每次余项最高次幂项与除数最高次幂项相除的值
        double first_data = remender.tail->data / myPoly.tail->data;
        int first_index = remender.tail->index - myPoly.tail->index;
        temp_top.Insert_And(first_data, first_index);   //暂时存起来,用来后面的乘法操作
        topPoly.Insert_And(first_data, first_index);      //插入到商的多项式中
        MyPoly temp_poly;
        temp_top.Mul(myPoly, temp_poly);         //也是一个暂时式，存放乘之后的值，便于后面相减
        /**
         * 得到最高次幂商之后 再乘以除数MyPoly2 得到中间多项式temp_poly
         * 下一步得到新的分子多项式（余项多项式）
         */
         //temp_poly = x5
        //temp_poly.print();
        //remender.print();
        Node *p = temp_poly.head;
        while (p != NULL) {
            if (p->data != 0)
                remender.Insert_Sub(p->data, p->index);
            p = p->next;
        }

        //cout << "余多项式为:";
        //remender.print();
        if (remender.tail->next != NULL) {
            MyPoly1_max_index = remender.tail->index;   //更新 新的最高次幂的大小
        }
        else if(remender.tail->next == NULL)
            break;
    }
    cout << "最终商为:";
    topPoly.print();
    topPoly.output();
    cout << "最终余项为:";
    remender.print();
    remender.output();
}