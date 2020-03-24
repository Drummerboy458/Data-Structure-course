//
// Created by Lww on 2018/11/2.
//

#ifndef HUFFMANCODE_HUFFNODE_H
#define HUFFMANCODE_HUFFNODE_H

#include <iostream>
using namespace std;
template <typename E>
class HuffNode {
private:
    E value ;   //值
    int weight = 0; //权重
    HuffNode<E>* lc = NULL; //左孩子
    HuffNode<E>* rc = NULL; //右孩子
public:
    string code = "";
     ~HuffNode()
    {

    }
    HuffNode<E>(E &val,int weight)
    {
         this->value = val;
         this->weight = weight;
    }
    HuffNode<E>(HuffNode<E>* rc,HuffNode<E>* lc)
    {
         this->lc = lc;
         this->rc = rc;
    }
     int getWeight()
     {
         if(this->isLeaf())     //当前节点为叶节点，返回自己的weight
             return weight;
         else
             return lc->getWeight() + rc->getWeight();  //内部节点,则返回其左右两颗weight之和
     }
     bool isLeaf()  //判断是否为叶节点
     {
         if(lc == NULL && rc == NULL)
             return true;
         else
             return false;
     }
     void setCode(string str)
     {
         this->code = str;
     }
     string getCode()
     {
         return code;
     }
     E getValue()
     {
         if(this->isLeaf()) //判断为叶节点才返回value值
             return value;
         else
             return NULL;
     }
     HuffNode<E>* getRight()   //得到指向右子树的节点的指针
     {
         if(!this->isLeaf())
         {
             return rc;
         }
     }
     HuffNode<E>* getLeft()
     {
         if(!this->isLeaf())
         {
             return lc;
         }
     }
};

#endif //HUFFMANCODE_HUFFNODE_H
