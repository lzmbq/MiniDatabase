/********************************************************************
	created:	2008/06/15
	created:	15:6:2008   23:02
	modified:	
	filename: 	
	file ext:	h
	author:		
	
	purpose:	
*********************************************************************/
#ifndef INDEX_H_
#define INDEX_H_
#include "AVLTree.h"
#include "Elem.h"
#include "MyBucket.h"
class Index
{
private:
	AVL<int, int, KEComp, EEComp>* m_AVLIndex;
	Bucket* m_HashIndex;
public:
	Index();
	~Index();
	bool HashInsert(const string& column, const int& tableBodyaddr);
	int HashGetAddr(int set[], const string& column);
	bool HashDelete(const string& column, const int& tableBodyaddr);

	bool AVLInsert(const int& e,const int& addr);
	bool AVLRemove(const int& k, BinNode<int>*& t);
	bool AVLFind(const int& K, int& e) const;
	bool AVLFindSet(const string& comp, const int& K, LList<int>*& set);
};

#endif