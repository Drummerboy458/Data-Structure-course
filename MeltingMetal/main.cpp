#include <iostream>
#include <fstream>
#include <queue>
using namespace std;
int result = 0;
int N = 0;  //N为方格边长的大小
char** pool = nullptr;//方格
int** vis = nullptr;// 标记是否空白，空白0，金属1
class Pos  //坐标类
{
public:
    int i = 0;
    int j = 0;
}temp1,temp2;
queue<Pos> q;//存放每一个节点
int mt[4][2] = {-1,0,0,1,1,0,0,-1};//遍历的四个方向
Pos start;  //开始遍历的点
bool Can_Melt(int x,int y)
{
    Pos temp;
    int count = 0;  //记录该节点周围为空的格子个数
    for(int i = 0;i < 4;i++)    //上下左右四个方向遍历
    {
        temp.i = x + mt[i][0];
        temp.j = y + mt[i][1];
        if(temp.i >= 0 && temp.i < N && temp.j >= 0 && temp.j < N && pool[temp.i][temp.j] == '_') //该金属这个方向为空
        {
            count++;
        }
    }
    if(count >= 2)  //至少两个方向邻接液体
    {
        return true;
    }
    else
    {
        return false;
    }
}
void Input()    //获得输入，且初始化标记
{
    ifstream inputfile ("inputfile.txt");
    cout<<"请输入方格的大小N:"<<endl;
    cin>>N;
    cout<<N<<endl;
    pool = new char* [N];    //给pool分配空间，完成初始化
    vis = new int* [N];
    for(int i = 0;i < N;i++)
    {
        pool[i] = new char[N];
        inputfile>>pool[i];
    }
    for(int i = 0;i < N;i++)
    {
        vis[i] = new int[N];
        for(int j = 0;j < N;j++)
        {
            if(pool[i][j] == '_')   //液体用0标记
                vis[i][j] = 0;
            if(pool[i][j] == '#')   //金属1标记
            {
                vis[i][j] = 1;
            }
            if(pool[i][j] == 'x')   //中空标记
            {
                vis[i][j] = 4;
            }
        }
    }
    inputfile.close();
}
void Output()
{
    for(int i = 0;i < N;i++)
    {
        for(int j = 0;j < N;j++)
        {
            cout<<pool[i][j];
        }
        cout<<endl;
    }
}
void Add_Sign() //每一次融化前遍历数组，标记要融化的点
{
    temp1.i = start.i = 0;
    temp1.j = start.j = 0;
    if (Can_Melt(temp1.i, temp1.j))
    {
        vis[temp1.i][temp1.j] = 2;
    }
    q.push(temp1);
    while (!q.empty())
    {
        temp1 = q.front();  //取到第一个节点
        q.pop();
        for (int i = 0; i < 4; i++)     //四个方向去搜索
        {
            temp2.i = temp1.i + mt[i][0];//方向
            temp2.j = temp1.j + mt[i][1];
            if (temp2.i >= 0 && temp2.i < N && temp2.j >= 0 && temp2.j < N && vis[temp2.i][temp2.j] != 5
            && vis[temp2.i][temp2.j] != 2 && vis[temp2.i][temp2.j] != 3 && vis[temp2.i][temp2.j] != 6)    //没被标记过
            {
                q.push(temp2);  //满足条件入栈
                if (pool[temp2.i][temp2.j] == '#')  //如果该节点是金属
                {
                    if (Can_Melt(temp2.i, temp2.j)) //能融化,标记为2
                    {
                        vis[temp2.i][temp2.j] = 2;
                    }
                    else
                        vis[temp2.i][temp2.j] = 3;  //此次不能融化，标记为3
                }
                if(pool[temp2.i][temp2.j] == 'x')    //该节点是中空的点
                {
                    Pos temp;
                    for(int c = 0;c <4;c++) //遍历该节点的四个方向
                    {
                        temp.i = temp2.i + mt[c][0];
                        temp.j = temp2.j + mt[c][1];
                        if(pool[temp.i][temp.j] == '_') //如果和外界连通，则该节点置为'_'
                        {
                            pool[temp2.i][temp2.j] = '_';
                        }
                    }
                    vis[temp2.i][temp2.j] = 5;  //标记此位置已经访问过
                }
                if(pool[temp2.i][temp2.j] == '_')   //液体
                {
                    vis[temp2.i][temp2.j] = 6;  //已访问
                }
            }
        }
    }
}
void Melt()
{
    for(int i = 0;i < N;i++)
    {
        for(int j = 0;j < N;j++)
        {
            if(vis[i][j] == 2)   //该位置金属融化,置为液体状态0
            {
                vis[i][j] = 0;
                pool[i][j] = '_';
            }
            if(vis[i][j] == 6)  //访问过的液体，恢复液体标记
            {
                vis[i][j] = 0;
            }
            if(vis[i][j] == 5)  //恢复中空的标记
            {
                vis[i][j] = 4;
            }
            else if(vis[i][j] == 3) //3为下一波次将可能融化的金属
            {
                vis[i][j] = 1;
            }
        }
    }
    result++;
    cout<<"time:"<<result<<"s"<<endl;
}

bool Is_Not_None()  //判断是否融化完成
{
    for(int i = 0;i < N;i++)
    {
        for(int j = 0;j < N;j++)
        {
            if(pool[i][j] == '#')
                return true;
        }
    }
    return  false;
}
int main()
{
    Input();
    Output();   //初始化打印出模型
    while(Is_Not_None())
    {
        Add_Sign();
        Melt();
        Output();
    }
}