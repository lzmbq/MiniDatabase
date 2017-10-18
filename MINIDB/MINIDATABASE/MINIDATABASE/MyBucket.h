/********************************************************************
	created:	2008/06/15
	created:	15:6:2008   23:02
	modified:	
	filename: 	MyBucket
	file ext:	h
	author:		
	
	purpose:	为索引完成HASH功能
*********************************************************************/
#ifndef BUCKET_H_
#define BUCKET_H_
#include "AList.h"
#include "LList.h"
#include <string>
using namespace std;
class BucketNode
{
public:
	string column;
	int tableBodyaddr;
};
class Bucket 
{
private:
	AList<BucketNode> A[30];
	int RSHash(const char* str)
	{
		unsigned int b = 378551 ;
		unsigned int a = 63689 ;
		unsigned int hash = 0 ;
		while (*str)
		{
			hash = hash * a + (*str ++ );
			a *= b;
		}
		return (hash & 0x1D ); // 0~29
	}
public:
	bool Insert(const string& column, const int& tableBodyaddr)
	{
		int addr;
		BucketNode bNode;
		addr = RSHash(column.c_str());
		bNode.tableBodyaddr = tableBodyaddr;
		bNode.column = column;
		A[addr].insert(bNode);
		return true;
	}
	int GetAddr(int set[], const string& column)
	{
		int addr, count;
		count = 0;
		BucketNode bNode;
		addr = RSHash(column.c_str());
		A[addr].setStart();
		for (int i = 0; i < A[addr].length(); i++)
		{
			A[addr].getValue(bNode);
			if (bNode.column == column)
			{
				set[count] = bNode.tableBodyaddr;
				count ++;
			}
			A[addr].next();
		}
		return count;
	}
	bool Delete(const string& column, const int& tableBodyaddr)
	{
		int addr;
		BucketNode bNode;
		addr = RSHash(column.c_str());
		A[addr].setStart();
		for (int i = 0; i < A[addr].length(); i++)
		{
			A[addr].getValue(bNode);
			if (bNode.tableBodyaddr == tableBodyaddr)
			{
				A[addr].remove(bNode);
			}
			A[addr].next();
		}
		return true;
	}
	
};

#endif