#include <iostream>
#include <fstream>
using namespace std;
int result = 0; //最大导通次数
int** Matrix = nullptr;//0-1矩阵
int* save_index = nullptr;
int N = 0;  //N行M列
int M = 0;
int k = 0;  //用户输入的激光照射的次数
void Input()    //获得输入,初始化矩阵
{
    ifstream fin ("inputfile.txt");
    cout<<"请输入扫描数k:"<<endl;
    cin>>k;
    cout<<"请输入矩阵的行数N:"<<endl;
    cin>>N;
    cout<<"请输入矩阵的列数M:"<<endl;
    cin>>M;
    save_index = new int[M];
    for(int i = 0;i < M;i++)    //初始化为-1，保存每次翻转列的索引
    {
        save_index[i] = -1;
    }
    Matrix = new int* [N+1];    //给matrix分配空间，完成初始化
    for(int i = 0;i < N+1;i++)
    {
        Matrix[i] = new int[M+1];
    }
    int temp = 0;
    for(int i = 0;i < N;i++)
    {
        for(int j = 0;j < M;j++)
        {
            fin>>temp;
            Matrix[i][j] = temp;
        }
    }
    fin.close();
}
void IsBreakOver(int** matrix)  //判断导通行数
{
    int time = 0;
    for(int i = 0;i < N;i++)
    {
        bool flag = true;
        for(int j = 0;j < M;j++)
        {
            if(matrix[i][j] == 0)
            {
                flag = false;
            }
        }
        if(flag == true)    //第i行导通
        {
            time++;
        }
    }
    cout<<"导通行数为"<<time<<endl;
    result = max(time,result);
}
void Reverse(int** matrix,int y) //反转y列
{
    for(int i = 0;i < N;i++)
    {

        if(matrix[i][y] == 0)
            matrix[i][y] = 1;
        else if(matrix[i][y] == 1)
            matrix[i][y] = 0;
    }
}
void Count_Row_Zero(int** matrix,int N,int M)   //统计每行0的个数
{
    int result;
    for(int i = 0;i < N;i++)
    {
        result = 0;
        for(int j = 0;j < M;j++)
        {
            if(matrix[i][j] == 0)
                result++;
        }
        matrix[i][M] = result;
    }
}
void Count_Col_Zero(int** matrix,int N,int M)   //统计每列0的个数
{
    int result;
    for(int j = 0;j < M;j++)
    {
        result = 0;
        for(int i = 0;i < N;i++)
        {
            if(matrix[i][j] == 0)
                result++;
        }
        matrix[N][j] = result;
    }
}
void Swap_Row(int** matrix,int x,int y) //交换x与y行
{
    for(int j = 0;j < M+1;j++)
    {
        int temp = matrix[x][j];
        matrix[x][j] = matrix[y][j];
        matrix[y][j] = temp;
    }
}
void Swap_Col(int** matrix,int x,int y,int N)  //交换x与y两列
{
    for(int i = 0;i < N+1;i++)
    {
        int temp = matrix[i][x];
        matrix[i][x] = matrix[i][y];
        matrix[i][y] = temp;
    }
}
void Sort_Row(int ** matrix,int N,int M)
{
    for(int i = 0;i < N;i++)
    {
        for(int j = 0;j < N-1-i;j++)
        {
            if(matrix[j][M] > matrix[j+1][M])
            {
                Swap_Row(matrix,j,j+1);
            }
        }
    }
}
void Sort_Col(int ** matrix,int N,int M)
{
    for(int i = 0;i < M;i++)
    {
        for(int j = 0;j < M-1-i;j++)
        {
            if(matrix[N][j] < matrix[N][j+1])
            {
                Swap_Col(matrix,j,j+1,N);
            }
        }
    }
}
void Sort_Matrix(int** matrix,int n,int m)
{
    Count_Row_Zero(matrix,n,m);
    Count_Col_Zero(matrix,n,m);
    Sort_Row(matrix,n,m);
    Sort_Col(matrix,n,m);
    cout<<endl;
}
void Output(int** matrix,int n,int m)
{
    //Sort_Matrix(matrix,n-1,m-1);
    for(int i = 0;i < n;i++)
    {
        for(int j = 0;j < m;j++)
        {
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}
void flip_back()
{
    int x = 0;
    for(int i = 0;i < M;i++)
    {
        if(save_index[i] != -1)
        {
            x = save_index[i];
            Reverse(Matrix,x);
        }
    }
}
void flip(int x)    //反转x行中0的列
{
    for(int j = 0,h = 0;j < M;j++ )
    {
        if(Matrix[x][j] == 0)
        {
            Reverse(Matrix,j);
            save_index[h] = j;
            h++;
        }
    }
    cout<<"选择第"<<x+1<<"行进行翻转,";
    IsBreakOver(Matrix);
    Output(Matrix,N+1,M+1);
    cout<<endl;
    flip_back();    //恢复此次翻转的影响，以测试下一轮
}
bool find(int x)
{
    for(int i = 0;i < N;i++)
    {
        if (Matrix[i][M] == x)
        {
            return true;
        }
    }
    return false;
}
void find_flip(int x)    //找到0个数为x的那一行,翻转x行中0的列
{
    for(int i = 0;i < N;i++)
    {
        if (Matrix[i][M] == x)
        {
            flip(i);
        }
    }
}
    int main()
{
    Input();
    Sort_Matrix(Matrix,N,M);
    Output(Matrix,N+1,M+1);
    for(k;k > 0;k -= 2)
    {
        if(find(k))
            cout<<"翻转"<<k<<"次,有如下情况:"<<endl;
        find_flip(k);  //3 = k..k -2..k-4
    }
    cout<<"最大导通行数为:"<<result<<endl;
}