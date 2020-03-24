#include <iostream>
#include <stack>
#include "function.h"
using namespace std;
int main() {
    int MazeMap [size][size] =
            {       { 1,1,1,1,1,1,1,1,1,1,1,1}, {1,0,0,0,0,0,0,0,0,0,0,1},{0,0,0,0,0,0,0,0,0,0,0,1},{1,1,1,0,1,0,0,0,0,1,0,1}
                    ,{1,0,0,0,0,1,1,1,0,1,0,0},{1,1,1,1,0,1,0,1,0,1,0,1},{1,0,0,1,0,1,0,1,0,1,0,1},{1,1,0,1,0,1,0,1,0,1,0,1}
                    ,{1,0,0,0,0,0,0,0,0,1,0,1},{1,1,1,1,1,1,0,1,1,1,0,1},{1,0,0,0,0,0,0,1,0,0,0,1},{1,1,1,1,1,1,1,1,1,1,1,1}
            };
    printMaze(MazeMap,size);
    cout<<endl;
    stack<Pos> path;    //保存走过路径
    stack<Pos> shortestpath;//保存最短路径
    Pos entry = { 2,0 };    //迷宫入口
    GetTheWayR(MazeMap, size,entry,path,shortestpath);
    int size = shortestpath.size();
    printShortPath(MazeMap,shortestpath,size);
    return 0;
}
