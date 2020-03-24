//
// Created by Lww on 2018/11/10.
//

#ifndef MAZE_FUNCTION_H
#define MAZE_FUNCTION_H

#include <iostream>
#include <stack>
using  namespace std;
const int size = 12;
struct Pos  //坐标类
{
    int i;
    int j;
};
bool IsGoingR(int maze[][size], int size, Pos cur, Pos next)    //cur为当前坐标，next为下一个要判断的坐标
{
    if (next.i < size && next.i >= 0 && next.j < size && next.j >= 0)   //判断是否出界
    {
        if (maze[next.i][next.j] == 0)  //判断当前元素是否为0,可以走
        {
            return true;
        }
    }
    return false;
}
void printShortPath(int MazeMap[][size],stack<Pos> shortestpath,int n)
{
    for(int i = 0;i < n;i++)
    {
        MazeMap[shortestpath.top().i][shortestpath.top().j] = 2;    //最短路径标记为2
        shortestpath.pop(); //pop掉已经标记的位置
    }
    for (int i = 0;i < size;i++)
    {
        for (int j = 0;j < size;j++)
        {
            if(MazeMap[i][j] == 2)
            {
                cout << "#" << " ";
            }
            else if(MazeMap[i][j] == -1)
                cout << "X"<<" ";
            else
                cout << MazeMap[i][j]<<" ";
        }
        cout << endl;
    }
}
void printMaze(int MazeMap[][size],int size)
{
    for (int i = 0;i < size;i++)
    {
        for (int j = 0;j < size;j++)
        {
            cout << MazeMap[i][j]<<" ";
        }
        cout << endl;
    }
}
bool GetTheWayR(int maze[][size], int size, Pos pos, stack<Pos>& path,stack<Pos>& shortestpath) {
    path.push(pos); //当前位置坐标入栈
    Pos next;
    next = pos;
    next.i = pos.i - 1;     //上方向
    if (IsGoingR(maze, size, pos, next))
    {
        maze[next.i][next.j] = -1;
        if (GetTheWayR(maze, size, next, path,shortestpath))
        {
            return true;
        }
    }
    next = pos;
    next.j = pos.j + 1;     //右方向
    if (IsGoingR(maze, size, pos, next))
    {

        maze[next.i][next.j] = -1;
        if (GetTheWayR(maze, size, next, path,shortestpath))
        {
            return true;
        }
    }

    next = pos;
    next.i = pos.i + 1;     //下方向
    if (IsGoingR(maze, size, pos, next))
    {
        maze[next.i][next.j] = -1;
        if (GetTheWayR(maze, size, next, path,shortestpath))
        {
            return true;
        }
    }
    next = pos;
    next.j = pos.j - 1;     //左方向
    if (IsGoingR(maze, size, pos, next))
    {

        maze[next.i][next.j] = -1;
        if (GetTheWayR(maze, size, next, path,shortestpath))
        {
            return true;
        }
    }
    if(pos.j == size - 1)   //到达出口的边界上
    {
        if(path.size() < shortestpath.size() || shortestpath.empty())   //更新保存最短路径的栈
        {
            shortestpath = path;
        }
        cout<<"最短路径走的步数为:";
        cout<<shortestpath.size()<<endl;
        cout<<"标有'#'为最短路径"<<endl;
    }
    path.pop(); //分叉返回时，把走过的那个位置给pop掉
    return 0;
}

#endif //UNTITLED1_FUNCTION_H
