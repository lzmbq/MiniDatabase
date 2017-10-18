#include "Index.h"

Index::Index()
{
	m_HashIndex = new Bucket();
	m_AVLIndex = new AVL<int, int, KEComp, EEComp>();
}

Index::~Index()
{
	delete m_HashIndex;
	delete m_AVLIndex;
}
bool Index::HashInsert(const string& column, const int& tableBodyaddr)
{
	return m_HashIndex->Insert(column, tableBodyaddr);
}
int Index::HashGetAddr(int set[], const string& column)
{
	return m_HashIndex->GetAddr(set, column);
}
bool Index::HashDelete(const string& column, const int& tableBodyaddr)
{
	return m_HashIndex->Delete(column, tableBodyaddr);
}

bool Index::AVLInsert(const int& e,const int& addr)
{
	return m_AVLIndex->insert(e, addr);
}
bool Index::AVLRemove(const int& k, BinNode<int>*& t)
{
	return m_AVLIndex->remove(k, t);
}
bool Index::AVLFind(const int& K, int& e) const
{
	return m_AVLIndex->find(K, e); 
}
bool Index::AVLFindSet(const string& comp, const int& K, LList<int>*& set)
{
	return m_AVLIndex->findSet(comp, K, set);
}