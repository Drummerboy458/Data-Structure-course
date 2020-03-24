#include <iostream>
#include <cstring>
#include <limits>
#include "BTree.h"
using namespace std;
void Menu() {
    cout << "========B-Trees 的设计与实现========" << endl;
    cout << "操作说明("<<"()为一个节点，其中两边有||的是非叶子节点):" << endl;
    cout << "1.建立B-Tree" << endl;
    cout << "2.遍历输出B-Tree" << endl;
    cout << "3.删除元素" << endl;
    cout << "4.插入元素" << endl;
    cout << "5.查找指定元素" << endl;
    cout << "6.退出" << endl;
}
int main()
{
    Menu();
    BTree<int>* bt = nullptr;
    bool flag = true;
    while (flag) {
        cout << "请输入操作编号:";
        int n;
        cin.clear();
        cin.sync();
        cin >> n;
        switch (n) {
            case 1:
                if (bt != nullptr) {
                    cout << "树已经存在!" << endl;
                    continue;
                }
                else
                    {
                    cout << "输入度数m和元素个数n:";
                    int m, n;
                    cin >> m >> n;
                    if (m < 2) {
                        cout << "度数太小!" << endl;
                        continue;
                    }
                    bt = new BTree<int>(m);
                    cout << "输入" << n << "个整数:" << endl;
                    for (int i = 0;i < n;++i)
                    {
                        int c;
                        cin >> c;
                        bt->B_Tree_Insert(c);//插入输入的每个元素
                    }
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  //把回车之前输入的数据清除
                    bt->Print();//第一次插入完成后打印出树形
                }
                break;
            case 2:
                if (bt == nullptr) {
                    cout << "当前没有建立B树!" << endl;
                }
                else if (bt->size() <= 0) {
                    cout << "B树中无元素!" << endl;
                }
                else {
                    bt->Print();
                }
                break;
            case 3:
                if (bt == nullptr) {
                    cout << "当前没有建立B树!" << endl;
                }
                else if (bt->size() <= 0) {
                    cout << "B树中无元素!" << endl;
                }
                else {
                    cout << "请输入要删除的元素:";
                    int k;
                    while(cin>>k)
                    {
                        if (bt->B_Tree_Search(k))
                        {
                            bt->B_Tree_Delete(k);
                        }
                        else
                        {
                            cout << "未找到相应的关键字" << k << "!" << endl;
                        }
                        char temp = cin.get();
                        if(temp == '\n')
                            break;
                    }
                    bt->Print();
                }
                break;
            case 4:
                if (bt != nullptr) {
                    cout << "请输入插入的元素:";
                    int k;
                    while(cin >> k) //连续插入关键字
                    {
                        if(bt->B_Tree_Search(k))
                        {
                            cout<<"有重复的关键字"<<k<<"!"<<endl; //有重复关键字，忽略
                            cin.sync();
                        }
                        else
                        {
                            bt->B_Tree_Insert(k);
                        }
                        char temp = cin.get();
                        if(temp == '\n')
                            break;
                    }
                    bt->Print();
                }
                else {
                    cout << "B树未建立！" << endl;
                }
                break;
            case 5:
                cout<<"请输入您要查找的元素值:"<<endl;
                int k;
                cin>>k;
                if(bt->B_Tree_Search(k)) {
                    cout<<"该元素存在!"<<endl;
                }
                else{
                    cout<<"该元素不存在！"<<endl;
                }
                break;
            case 6:
                delete bt;//释放占用内存
                bt = nullptr;
                flag = false;
                break;
            default:
                cout << "输入无效!" << endl;
                cin.clear();            //clear bad input flag 输入的数据不符合规定，更改cin的状态标示符为0
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  //把回车（包括回车）之前的所以字符从输入缓冲（流）中清除出去
        }
    }
    return 0;
}
