//
// Created by Lww on 2018/11/2.
//

#ifndef HUFFMANCODE_HUFFTREE_H
#define HUFFMANCODE_HUFFTREE_H

#include "HuffNode.h"
#include <iostream>
template <typename E>
class HuffTree {
private:
    HuffNode<E>* root;  //树的根
public:
    HuffTree(E& val,int freq)
    {
        root = new HuffNode<E>(val,freq);
    }
    HuffTree(HuffTree<E>* l,HuffTree<E>* r)
    {
        root = new HuffNode<E>(l->getRoot(),r->getRoot());
    }
    ~HuffTree()
    {

    };
    HuffNode<E>* getRoot()
    {
        return root;
    }
    int getWeight()
    {
        return root->getWeight();    //获得Root的权重
    }
    void swap(HuffTree<char>* &x,HuffTree<char>* &y)
    {
        HuffTree<char>* temp = x;
        x = y;
        y = temp;
    }
};


#endif //HUFFMANCODE_HUFFTREE_H
