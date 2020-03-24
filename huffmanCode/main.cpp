#include <iostream>
#include "function.h"
using namespace std;
int main()
{
    string source = getEncodeSource();  //获取要编码的字符串
    int length = count(source);     //统计源编码文件不同字符的个数
    cout<<"inputfile1.txt里各字符编码后的结果为:"<<endl;
    cout<<"字符    "<<"出现次数   "<<"对应的编码   "<<endl;
    vector<HuffTree<char>*> hufftree = Encode(source);//得到初始时编码后装有根节点的vector
    deCode(hufftree,source,length);//传入到deCode函数，从而初始化codeMap,进行解码
    return 0;
}