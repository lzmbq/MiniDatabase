/********************************************************************
	created:	2008/06/15
	created:	15:6:2008   23:02
	modified:	
	filename: 	TableBody
	file ext:	h
	author:		
	
	purpose:	对表体的抽象，实现对记录的增删查改操作
*********************************************************************/
#ifndef TableBody_H_
#define TableBody_H_
#include <iostream>
using namespace std;

//const int DefaultListSize = 100;

template<class T>
class TableNode
{
	public:
		T data;
		bool state;
		int link;
};
template <class T>
class TableBody
{
public:
	TableBody(int MaxSpaceSize = 300);
	~TableBody();
	int Allocate(T v);
	void Deallocate(int& i);
	T GetValue(int i) const;
	int GetLength() const;
	int GetAvailableData(int i) const;
	bool Updata(const T& v, int addr);
private:
	int NumberOfNodes, first;
	TableNode<T>* node;
	int length;
};

template <class T>
TableBody<T>::TableBody(int MaxSpaceSize)
{
	NumberOfNodes = MaxSpaceSize;
	node = new TableNode<T>[NumberOfNodes];
	for (int i = 0; i < NumberOfNodes-1; i++)
	{
		node[i].link = i+1;
		node[i].state = false;
	}
	node[NumberOfNodes-1].link = -1;
	first=0;
	length=0;
}

template <class T>
TableBody<T>::~TableBody()
{
	delete [] node;
}

template <class T>
int TableBody<T>::Allocate(T v)
{
	if(first == -1)
	{
		return -1;
		cout << "该链表到结尾了~ "<<endl;
	}
	int i = first;
	node[i].state = true;
	first = node[i].link;
	//
	node[i].data=v;
	length++;
	return i;
}

template <class T>
void TableBody<T>::Deallocate(int& i)
{
	node[i].state = false;
	node[i].link = first;
	first = i;
	length--;
}

template <class T>
T TableBody<T>::GetValue(int i) const
{
	return node[i].data;
}

template <class T>
int TableBody<T>::GetLength() const
{
	return this->length;
}
template <class T>
int TableBody<T>::GetAvailableData(int i) const
{
	if (this->length < i)
	{
		cout << "超出了TableBody的长度！" << endl;
		return -1;
	}
	int count = 0;
	for (int t = 0; t < 30; t++) //TableBody Total Length
	{
		if (node[t].state == true)
			count ++;
		if (count == i)
			return t;
	}
	return -1;
}
template <class T>
bool TableBody<T>::Updata(const T& v, int addr)
{
	node[addr].data = v;
	return true;
}
// 使用两个可利用空间表
/*
template <class T>
TableBody<T>::TableBody(int MaxSpaceSize)
{
	NumberOfNodes = MaxSpaceSize;
	node = new TableNode<T>[NumberOfNodes];

	first1 = 0;
	first2 = -1;
}

template <class T>
int TableBody<T>::Allocate()
{
	if (first2 == -1)
	{
		if (first1 == NumberOfNodes)
			cout << "overflow!";
		return fisrt1++;
	}
	int i = first2;
	first2 = node[i].link;
	return i;
}

template <class T>
void TableBody<T>::DeallocateCircular(int& c)
{
	if (c != -1)
	{
		int next = node[c].link;
		node[c].link = first;
		first = next;
		c = -1;
	}
}*/
#endif