#include <iostream>
#include <queue>
using namespace std;
struct Pos  //坐标类
{
    int i;
    int j;
}temp1,temp2;
const int size = 6;

Pos pre[10][10];  //坐标数组，保存其前驱的坐标
Pos ans[30];    //记录回去的路径
int vis[6][6];//用来标记的走没走过
int mt[4][2] = {-1,0,0,1,1,0,0,-1};//遍历的四个方向
queue<Pos> q;   //存放节点
void print(int Map[][size],int size)
{
    for(int i = 0;i < size;i++)
    {
        for(int j = 0;j < size;j++)
        {
            if(Map[i][j] == -1)
                cout<<"a"<<" ";
            else if(Map[i][j] == -2)
                cout<<"b"<<" ";
            else if(Map[i][j] == -3)    //-3 为必须避开的区域
                cout<<"X"<<" ";
            else if(Map[i][j] == -4)
                cout<<"#"<<" ";
            else
                cout<<Map[i][j]<<" ";
        }
        cout<<endl;
    }
}
int main()
{
    int Map [size][size] = {{ 0,0,0,0,0,0}, {0,0,-3,0,0,0},{0,0,-3,0,0,0},{0,0,-3,0,0,0},{-3,-3,-3,0,0,0},{0,0,0,0,0,0}};//-3 为必须避开的区域
    Pos start,end;
    int sx ;
    int sy ;
    int ex ;
    int ey ;
    cout<<"请输入需要布线的位置,起点坐标:";
    cin>>sx>>sy;
    cout<<"请输入终点坐标:";
    cin>>ex>>ey;
    start.i = sx;
    start.j = sy;
    end.i = ex;
    end.j = ey;
    if(Map[sx][sy] == -3 || Map[ex][ey] == -3)
    {
        cout<<"输入坐标无效！"<<endl;
        return 0;
    }
    Map[sx][sy] = -1;
    Map[ex][ey] = -2;
    cout<<"下图为电路板,标记'X'为必须避开的区域"<<endl;
    print(Map,size);
    //初始化标记
    for(int  i = 0;i < size;i++)
    {
        for(int j = 0;j < size;j++)
        {
            vis[i][j] = 0;  //初始化为0，表示没走过
        }
    }
    temp1.i = sx;
    temp1.j = sy;
    vis[temp1.i][temp1.j] = 1;  //首先压入队列
    q.push(temp1);
    bool flag = false;
    while(!q.empty())
    {
        temp1 = q.front();  //取到第一个节点
        q.pop();
        for (int i = 0; i < 4; i++)     //四个方向去搜索
        {
            temp2.i = temp1.i + mt[i][0];//方向
            temp2.j = temp1.j + mt[i][1];
            if (temp2.i >= 0 && temp2.i < size && temp2.j >= 0 && temp2.j < size && !vis[temp2.i][temp2.j]//且没有被标记过
                && Map[temp2.i][temp2.j] != -3 )
            {
                //判断条件
                vis[temp2.i][temp2.j] = vis[temp1.i][temp1.j] + 1;//原来的位置加一,标记为走过
                Map[temp2.i][temp2.j] = vis[temp1.i][temp1.j];  //因为初始化vis[temp1.i][temp1.j] = 1,直接=
                q.push(temp2);  //满足条件入栈
                pre[temp2.i][temp2.j].i = temp1.i;//保存前一个位置的横坐标
                pre[temp2.i][temp2.j].j = temp1.j;//保存前一个位置的纵坐标
            }
        }
        if (vis[ex][ey])//如果到达终点就标记一下，表示能到达终点,break
        {
            Map[ex][ey] = -2;   //恢复终点标记
            flag = true;
            break;
        }
    }
    if(flag)
        cout<<"能到达终点!最短路径如下:"<<endl;
    else
        cout<<"不能到达终点!"<<endl;
    int lastx = ex, lasty = ey;//终点的位置
    int x, y, num = 0;
    bool flag1 = true;
    while(flag1)
    {
        ans[num].i = lastx;//ans 来记录一下
        ans[num].j = lasty;
        num++;

        x = lastx;
        y = lasty;
        lastx = pre[x][y].i;//读取下一个，也就是之前保存的前一个
        lasty = pre[x][y].j;
        if(lastx == sx && lasty == sy)  //到达终点
            flag1 = false;

    }
    for(int i = num;i > 0;i--)
    {
        Map[ans[i].i][ans[i].j] = -4;   //标记最短路径
    }
    print(Map,6);
}