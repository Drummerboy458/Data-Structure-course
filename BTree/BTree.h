#ifndef BTREE_H
#define BTREE_H

#include<cstdlib>
#include <iostream>
#include<queue>
using namespace std;
template<typename T>
class Node {
public:
	int n;//当前节点关键字的个数
	struct Node<T>** child;   //存放孩子的指针数组
	T* key;    //存放关键字的数组
	bool leaf;  //是否为叶子的标记
	Node(int t = 0)
	{
		n = t;
		child = nullptr;
		key = nullptr;
		leaf = true;
	}
	~Node()
	{
		n = 0;
		child = nullptr;
		key = nullptr;
	}
};
template<typename T>
class BTree {
private:
	//基础数据
	Node<T>* root;	//根结点
	int t;          //度数，默认是2
	int key_num;   //总的关键字个数

	//释放整个占用的空间，给析构函数调用
	void PostOrder_Delete(Node<T>*& cur);  //后根次序删除

	//查找部分
	Node<T>* search(Node<T>* r, const T& elem);

	//插入部分
	void B_Tree_Split_Child(Node<T>* x, int i);//x的i孩子裂变
	void Insert(Node<T>* &r, const T& k);//这里一点要传入指针的引用，否则会无法完成实际树的增长
	void B_Tree_Insert_NonFull(Node<T>* x, const T& k); //插入非空元素

	//删除部分
	void Merge_Node(Node<T>*& x, int i, Node<T>*& y, Node<T>*& z);  //和并x的第i个子结点y和第i+1个子结点z，此时y和z的key个数都是t-1
	T Search_Predecessor(Node<T>* y); //查找前驱
	T Search_Successor(Node<T>* z);   //查找后继
	void Shift_To_Left_Child(Node<T>*& x, int i, Node<T>*& y, Node<T>*& z);
	void Shift_To_Right_Child(Node<T>*& x, int i, Node<T>*& y, Node<T>*& z);
	void B_Tree_Delete_NoNone(Node<T>* x, const T &k);//删除内部结点x的k
public:
    BTree(int m = 2)
    {
    	t = m;
    	root = new Node<T>;
    	key_num = 0;
    }
	~BTree()
	{
    	PostOrder_Delete(root);
    }
	Node<T>* B_Tree_Search(const T& elem)  //查找元素
	{
    	return search(root, elem);
	}
    void B_Tree_Insert(const T& k) //插入元素k
    {
    	Insert(root, k);
    }
	void B_Tree_Delete(const T &k);					    //删除元素k
	void Print();										//结构化输出
    int size()const { return key_num; }                //返回元素的个数
};
template<typename T>
Node<T>* BTree<T>::search(Node<T>* x, const T& k)
{
	int i = 0;
	while (i<x->n && k>x->key[i])
	{
		++i;
	}
	if (i < x->n && k == x->key[i])
	{
		return x; //找到了，返回地址
	}
	else if (x->leaf) //未找到，返回空
	{
		return nullptr;
	}
	else {
		return search(x->child[i], k);   //尾递归的向下查找
	}
}
template<typename T>
void BTree<T>::Insert(Node<T>* &r, const T& k)
{
	if (B_Tree_Search(k))	//已存在k，则忽略跳出
	{
		return;
	}
	else if (r != nullptr && r->n == 2 * t - 1)	//达到最大的关键字数目
	{
		Node<T>* s = new Node<T>;	//新分配一个内部结点存放该值
		s->leaf = false;
		s->child = new Node<T>*[1];	//目前只有两个孩子
		s->child[0] = r;
		r = s;
		s->n = 0;
		B_Tree_Split_Child(s, 0);	//先分裂，满足B树结构，再插入
		B_Tree_Insert_NonFull(s, k);
	}
	else {
		B_Tree_Insert_NonFull(r, k);
	}
	key_num++;  //结点个数增加
}
template<typename T>
void BTree<T>::B_Tree_Split_Child(Node<T>* x, int i) //i是数组的下标
{
	Node<T>* y = x->child[i];
	Node<T>*L, *R;   //L R是新裂变的两个片段
	L = new Node<T>;
	R = new Node<T>;
	L->n = R->n = t - 1;
	L->key = new T[t - 1];
	R->key = new T[t - 1];
	L->leaf = R->leaf = x->child[i]->leaf;  //更改孩子的属性
	//复制键值
	for (int j = 0;j <= t - 2;++j)
	{
		L->key[j] = y->key[j];
		R->key[j] = y->key[j + t];
	}
	if (!y->leaf)
	{
		L->child = new Node<T>*[t];
		R->child = new Node<T>*[t];
		for (int j = 0;j < t;++j)
		{
			L->child[j] = y->child[j];
			R->child[j] = y->child[j + t];
		}
	}
	//处理x
	x->key = (T*)realloc(x->key, (x->n + 1) * sizeof(T));
	x->child = (Node<T>**)realloc(x->child, (x->n + 2) * sizeof(Node<T>*));
	for (int j = x->n - 1;j >= i;--j) //键值后移一位,保证大小关系
	{
		x->key[j + 1] = x->key[j];
	}
	x->key[i] = y->key[t - 1];
	for (int j = x->n;j >= i + 1;--j)
	{
		x->child[j + 1] = x->child[j];
	}
	x->child[i] = L;
	x->child[i + 1] = R;
	x->n++;
	//销毁原来的空间
	delete[] y->child;
	delete[] y->key;
	delete y;
}
template<typename T>
void BTree<T>::B_Tree_Insert_NonFull(Node<T>* x, const T& k)
{
	int i = x->n - 1;//倒序搜索
	if (x->leaf)
	{  //叶子结点直接插入
		x->key = (T*)realloc(x->key, (x->n + 1) * sizeof(T));//插入，比当前大小多一
		while (i >= 0 && k < x->key[i])
		{
			x->key[i + 1] = x->key[i];
			--i;
		}
		x->key[i + 1] = k;
		++x->n;
	}
	else {
		while (i >= 0 && k < x->key[i])//找到刚好比k小的孩子的位置下标
		{
			--i;
		}
		++i;
		if (x->child[i]->n == 2 * t - 1)	//先判断是否为满
		{
			B_Tree_Split_Child(x, i);
			if (k > x->key[i])	//在大于k值得右孩子子树里匹配k值
			{
				++i;
			}
		}
		B_Tree_Insert_NonFull(x->child[i], k);  //尾递归，直到该子树的叶子节点上
	}
}
template<typename T>
void BTree<T>::Merge_Node(Node<T>*& x, int i, Node<T>*& y, Node<T>*& z)	//合并x的第i个孩子节点y和第i+1个节点z
{
	y->key = (T*)realloc(y->key, (2 * t - 1) * sizeof(T));//重新分配大小
	for (int j = 0;j < t - 1;++j)
	{
		y->key[t + j] = z->key[j];
	}
	//不是叶子结点的情况下，还需要复制孩子
	if (!y->leaf)
	{
		y->child = (Node<T>**)realloc(y->child, 2 * t * sizeof(Node<T>**));
		for (int j = 0;j < t;++j)
		{
			y->child[t + j] = z->child[j];
		}
	}
	y->key[t - 1] = x->key[i];  //移动x的结点补充到y
	y->n = 2 * t - 1;//y节点满
	//删除x的下移关键字
	for (int j = i;j < x->n - 1;++j)
	{
		x->key[j] = x->key[j + 1];
	}
	x->key = (T*)realloc(x->key, (x->n - 1) * sizeof(T));
	//删除原来指向z的指针
	for (int j = i + 1;j <= x->n - 1;++j)
	{
		x->child[j] = x->child[j + 1];	//左移一个单位
	}
	x->child = (Node<T>**)realloc(x->child, (x->n) * sizeof(Node<T>**));
	x->child[i] = y;
	--x->n;
	//释放掉结点z
	delete[] z->key;
	delete[] z->child;
	delete z;
	z = nullptr;
}
template<typename T>
T BTree<T>::Search_Predecessor(Node<T>* y)//找y的后继
{
	Node<T>* x = y;//->child[y->n];
	while (!x->leaf)
	{
		x = x->child[x->n];
	}
	return x->key[x->n - 1];
}
template<typename T>
T BTree<T>::Search_Successor(Node<T>* z)//找z的前驱
{
	Node<T>* x = z;//->child[0];
	while (!x->leaf)
	{
		x = x->child[0];
	}
	return x->key[0];
}
template<typename T>
//把 x 的第 i + 1 右孩子 z 的一个结点 转移给 z 的左兄弟 y
void BTree<T>::Shift_To_Left_Child(Node<T>*& x, int i, Node<T>*& y, Node<T>*& z)
{
	if (y == nullptr)
	{  //防止出现空指针
		y = new Node<T>;
	}
	++y->n;
	//复制键值
	y->key = (T*)realloc(y->key, y->n * sizeof(T));
	y->key[y->n - 1] = x->key[i];
	x->key[i] = z->key[0];
	for (int j = 0;j < z->n - 1;++j)
	{
		z->key[j] = z->key[j + 1];	//左移填充空位
	}
	//非叶子结点的情况下复制孩子
	if (!z->leaf)
	{
		y->child = (Node<T>**)realloc(y->child, (y->n + 1) * sizeof(Node<T>*));
		y->child[y->n] = z->child[0];
		for (int j = 0;j < z->n;++j)
		{
			z->child[j] = z->child[j + 1];
		}
		z->child = (Node<T>**)realloc(z->child, z->n * sizeof(Node<T>*));
	}
	--z->n;
	z->key = (T*)realloc(z->key, z->n * sizeof(T));
}
template<typename T>
//把x的第i左孩子y的一个结点转移给y的右兄弟z
void BTree<T>::Shift_To_Right_Child(Node<T>*& x, int i, Node<T>*& y, Node<T>*& z)
{
	if (z == nullptr)
	{ //防止出现空指针
		z = new Node<T>;
	}
	++z->n;
	//复制键值
	z->key = (T*)realloc(z->key, z->n * sizeof(T));
	for (int j = z->n - 1;j > 0;--j)
	{
		z->key[j] = z->key[j - 1];	//往右移
	}
	z->key[0] = x->key[i];
	x->key[i] = y->key[y->n - 1];
	//非叶子结点的情况下复制孩子
	if (!z->leaf)
	{
		z->child = (Node<T>**)realloc(z->child, (z->n + 1) * sizeof(Node<T>*));
		for (int j = 0;j < z->n;++j)
		{
			z->child[j + 1] = z->child[j];
		}
		z->child[0] = y->child[y->n];
		y->child = (Node<T>**)realloc(y->child, y->n * sizeof(Node<T>*));
	}
	--y->n;
	y->key = (T*)realloc(y->key, y->n * sizeof(T));
}
template<typename T>
void BTree<T>::B_Tree_Delete_NoNone(Node<T>* x, const T &k)//删除内部结点x中的元素 k
{
	////关键字 k 在内部结点 x 中,分三种情况讨论
	if (x->leaf)
	{   //情况1 关键字k在结点x中,x是叶结点,直接在x中删除k
		int i = 0;
		while (i<x->n && k>x->key[i])
		{
			++i;
		}
		if (i < x->n && k == x->key[i])
		{
			for (int j = i + 1; j < x->n; ++j)
			{
				x->key[j - 1] = x->key[j];
			}
			--x->n;
			x->key = (T *) realloc(x->key, x->n * sizeof(T));
		}
	}
	else {
		int i = 0;
		while (i<x->n && k>x->key[i])
		{
			++i;
		}
		Node<T> *y = x->child[i], *z = nullptr;
		if (i < x->n)
		{
			z = x->child[i + 1];
		}
		if (k == x->key[i])
		{
			/*情况2 关键字 k 在结点 x 中,x 是内部结点
			*/
			if (y->n > t - 1)
			{
				/*情况2a 结点x前于k的子结点y至少含有t个关键字,找出k在以y为根的子树中的前 驱k′
				* ,递归地删除k′,并在x中用k′ 代替k.
				* */
				T k1 = Search_Predecessor(y);
				B_Tree_Delete_NoNone(y, k1);
				x->key[i] = k1;
			}
			else if (z->n > t - 1)
			{
				/*情况2b 对称的情况,如果y中少于t−1个结点,检查结点x中后于k的子结点z.
			     * 如果z 有 t 个关键字, 则找出 k 在以 z 为根的子树中的后继 k′.
			     * 递归地删除 k′, 并在 x 中 用k′ 代替k;
			     */
				T k1 = Search_Successor(z);
				B_Tree_Delete_NoNone(z, k1);
				x->key[i] = k1;
			}
			else {
				/*情况2c y和z都只是有t−1个结点,则把k和z合并进入结点y,此时的x失去了k和
				* 指向 z 的指针, 释放 z, 递归地从 y 中删除 k
				*/
				Merge_Node(x, i, y, z);
				B_Tree_Delete_NoNone(y, k);
			}
		}
		else {
			/*情况3 关键字 k 不在内部结点 x 中, 则必包含于 x.ci 中. 如果 x.ci 只有 t−1 个关键字,
			*那么执行这两步保证下降到一个至少包含 t 个关键字的结点.
			*/
			Node<T>* p = nullptr;
			if (i > 0)
			{
				p = x->child[i - 1];
			}
			if (y->n == t - 1)
			{
				/*情况3 如果 x.ci 只有 t − 1 个关键字, 但它的兄弟至少有 t 个关键字,
				* 则把 x 中的某个关 键字下降到 x.ci 中, 讲 x.ci 的相邻左兄弟或右兄弟
				* 的一个关键字升至 x, 讲该兄弟 中相应的孩子指针移到 x.ci 中, 使 x.ci 增加一个关键字.
				*/
				//情况3a
				if (i > 0 && p->n > t - 1)	//给左兄弟借
				{
					Shift_To_Right_Child(x, i - 1, p, y);
				}
                else if (i<x->n && z->n>t - 1) //给右兄弟借
                {
					Shift_To_Left_Child(x, i, y, z);
				}
				//情况3b
				else if (i > 0)
				{
					Merge_Node(x, i - 1, p, y);  //向左侧结点合并
					y = p;
				}
				else {
					Merge_Node(x, i, y, z);      //向右侧合并
				}
			}
			B_Tree_Delete_NoNone(y, k);
		}
	}
}
template<typename T>
void BTree<T>::B_Tree_Delete(const T &k)
{
	Node<T>* r = root;
	if (root->n == 1 && root->child == nullptr)//删除最后一个元素
	{
		delete[] root->key;
		delete root;
		root = nullptr;
	}
	else if (root->n == 1)//根节点为1个关键字，但孩子非空，压缩根节点
	{
		Node<T> *y = root->child[0], *z = root->child[1];
		if (y->n == z->n && y->n == t - 1)//先判断，考虑左右孩子都为最小关键字的情况，此时应合并左右孩子
		{
			Merge_Node(root, 0, y, z);
			root = y;
			delete[] r->child;
			delete[] r->key;
			delete r;
			B_Tree_Delete_NoNone(y, k);
		}
		else {
			B_Tree_Delete_NoNone(root, k);
		}
	}
	else {
		B_Tree_Delete_NoNone(r, k);
	}
    --key_num;  //结点个数减少一个
}
template<typename T>
void BTree<T>::Print()
{
	cout<<"当前总的关键字个数为:"<<this->size()<<"个"<<endl;
    Node<T> *last = root;//last表示当前层的最右结点
	Node<T>* p = root;
    queue<Node<T>*>Q;
	if (p)	//把指向树的root指针压入队列
	{
		Q.push(p);
	}
	while (!Q.empty())
	{
		Node<T>* tmp = Q.front();
		Q.pop();
		if (!tmp->leaf)
		{
            cout << "|";
		}
        cout<<"(";
		for (int i = 0;i < tmp->n;++i)
		{
            cout << " "<<tmp->key[i]<<" ";
			if (tmp->child && i != tmp->n - 1)
			{
                cout << "|";
			}
		}
        cout<<")";
		if (!tmp->leaf)
		{   //不是叶子结点才有孩子
            cout<<"|";
			for (int i = 0;i < tmp->n + 1;++i)
			{
				Q.push(tmp->child[i]);
			}
		}
		if (!last->leaf && tmp == last)
		{
            cout<<endl;
			last = last->child[last->n];
		}
	}
	cout<<endl;
}
template<typename T>
void BTree<T>::PostOrder_Delete(Node<T>*& cur)
{
    if (cur->leaf)//直接删除叶子结点
    {
		delete[] cur->key;
		delete cur;
		cur = nullptr;
	}
    else { //递归地删除每个孩子
		for (int i = 0;i < cur->n + 1;++i)
		{
			PostOrder_Delete(cur->child[i]);
		}
		delete[] cur->key;
		delete cur;
		cur = nullptr;
	}
}

#endif
