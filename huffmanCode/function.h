//
// Created by Lww on 2018/11/4.
//
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include "HuffTree.h"
#include <fstream>
using namespace std;
/*
 * 首先第一步，统计"inputfile1.txt"里面各字符出现的次数
 * 第二步构造哈佛曼树
 */
//从inputfile1里读出要编码的字符串
string getEncodeSource()
{
    ifstream fin("inputfile1.txt");
    string source = "";
    char ch;
    int size = 0;
    fin.get(ch);
    while (!fin.eof())
    {
        source = source + ch;   //依次读取字符，并把它拼接到一起
        size++;
        fin.get(ch);
    }
    fin.close();
    return source;
}
int count(string target)   //统计不同的字符有多少种,从而确定树根节点初始化时的数目
{
    int result = 0;
    for(int i = 0;i < target.size();i++)
    {
        int index = 0;
        bool flag = true;
        for(int k = 0;k < i;k++)
        {
            if(i != 0 && target[i] == target[k])
                flag=false;                 //判断该字符在前面是否出现过
        }
        if(flag == true)
        {
            for(int k = i;k < target.size();k++)
            {
                if(target[i] == target[k])  //与后面的比较 相等则次数加1
                    index++;
            }
            result++;
        }
    }
    return result;
}

bool comp(HuffTree<char>* &x,HuffTree<char>* &y)     //从小到大排序,重写vector排序sort()
{
    if(x->getWeight() < y->getWeight())
        return true;
    else
        return  false;
}
HuffTree<char>* buildHuffTree(vector<HuffTree<char>*> treeArray)     //构造哈佛曼树
{
    vector< HuffTree<char>* >::iterator it = treeArray.begin();
    HuffTree<char>* temp1 = NULL;
    HuffTree<char>* temp2 = NULL;
    HuffTree<char>* temp3 = NULL;
    while(treeArray.size() >= 2)
    {
        temp1 = treeArray[0];   //取到最小的两个树节点
        temp2 = treeArray[1];
        temp3 = new HuffTree<char>(temp1, temp2);   //组成一个新的节点
        treeArray.erase(it);    //删除旧节点
        treeArray.erase(it);
        treeArray.push_back(temp3); //插入新节点
        sort(treeArray.begin(), treeArray.end(), comp);//重新排序
    }
    return temp3;
}
//这一步先序遍历哈佛曼树，完成编码
void preorder(HuffNode<char>* tree,string str,ofstream& out)
{
    string temp = str;
    if(tree->isLeaf())
    {
        cout << tree->getValue()<<"       ";    //输出字母到控制台
        cout<<tree->getWeight()<<"         ";
        out<<tree->getValue()<<"         ";
        out<<tree->getWeight()<<"         ";
        tree->setCode(str);
        cout<<tree->getCode()<<endl;        //输出字母对应编码到控制台
        out<<tree->getCode()<<endl;
    }
    if(tree->isLeaf())
    {
        return;
    }
    preorder(tree->getLeft(),temp += "0",out);
    temp = str; //保存它每次从子节点出来时的编码值
    preorder(tree->getRight(),temp += "1",out);
}
//匹配每个字符对应的编码,source为要解码的目标串，target为对应大小为n的字母的编码数组
void find(string source, map<string,char> codeMap,ofstream &out)
{
    cout<<"inputfile2.txt里的字符串解码结果为:";
    int length1 = source.length();
    string temp = "";
    for(int i = 0;i < length1;i++)
    {
        temp += source[i];
        map<string, char>::iterator iter;
        iter = codeMap.find(temp);  //在codeMap里查找temp对应的value值
        if(iter != codeMap.end())
        {
            cout<<iter->second;
            out<<iter->second;
            temp = "";  //恢复temp，继续下一轮的匹配
        }
    }
}
vector<HuffTree<char>*> Encode(string source)   //source为要编码的源字符串
{
    int length = count(source);
    HuffTree<char>** TreeArray = new HuffTree<char>*[length];   //为初始树的每个节点分配空间
    int h = 0;  //h的大小为不同字母的数量,也是要创建的树的根节点数量
    vector<HuffTree<char>*>  hufftree;
    int size = source.length();
    for(int i = 0;i < size;i++)
    {
        int times = 0;
        bool flag = true;
        for(int k = 0;k < i;k++)
        {
            if(i != 0 && source[i] == source[k])
                flag=false;                 //判断该字符在前面是否出现过
        }
        if(flag == true)
        {
            for(int k = i;k < size;k++)
            {
                if(source[i] == source[k])  //与后面的比较 相等则次数加1
                    times++;
            }
            TreeArray[h] = new HuffTree<char>(source[i],times); //将每个字母出现的次数和值赋值给每个树节点
            hufftree.push_back(TreeArray[h]);
            h++;
        }
    }
    sort(hufftree.begin(), hufftree.end(),comp);
    HuffTree<char>* result = buildHuffTree(hufftree);
    string str = "";
    ofstream outfile("outputfile1.txt");
    outfile<<"字符    "<<"出现次数   "<<"对应的编码   "<<endl;
    preorder(result->getRoot(),str,outfile);
    outfile.close();
    return hufftree;
}
void toInput2(string target,map<string,char> codeMap)   //将input1.txt的字符串的编码写到inputfile2.txt中
{
    ofstream outfile("inputfile2.txt");
    int length = target.length();
    for(int i = 0;i < length;i++)
    {
        map<string, char>::iterator iter;
        for(iter = codeMap.begin(); iter != codeMap.end(); iter++)
        {
            if(iter->second == target[i])
            {
                outfile<<iter->first;
            }
        }
    }
    outfile.close();
}
void deCode(vector<HuffTree<char>*> hufftree,string &str,int length)
{
    string target ; //读出解码的目标01串
    ifstream fin("inputfile2.txt");
    fin>>target;
    cout<<"inputfile2里要解码的字符串为:"<<target<<endl;
    map<string,char> codeMap;
    string str1;
    char ch2;
    for(int i = 0;i < length;i++)
    {

        str1 = hufftree[i]->getRoot()->getCode();
        ch2 = hufftree[i]->getRoot()->getValue();
        codeMap[str1] = ch2;    //key(编码)=>value(char)
    }
    //cout<<"map大小为:"<<codeMap.size()<<endl;
    map<string, char>::iterator iter;
    ofstream outfile2("outputfile2.txt");   //与outfile2.txt连接
    find(target,codeMap,outfile2);
    outfile2.close();
    toInput2(str,codeMap);
}
