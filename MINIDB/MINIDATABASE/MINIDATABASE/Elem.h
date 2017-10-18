/********************************************************************
	created:	2008/06/15
	created:	15:6:2008   23:02
	modified:	
	filename: 	MyBucket
	file ext:	h
	author:		
	
	purpose:	为索引完成HASH功能
*********************************************************************/
#ifndef ELEM_H_
#define ELEM_H_
//This is the element of login system

class KEComp
{
public:
	static bool lt(int key, int elem) {return key<elem;}
	static bool eq(int key, int elem) {return key==elem;}
	static bool gt(int key, int elem) {return key>elem;}
};

class EEComp
{
public:
	static bool lt(int e1, int e2)
	{ return e1<e2;}
	static bool eq(int e1, int e2)
	{ return e1==e2;}
	static bool gt(int e1, int e2)
	{ return e1>e2;}
};
#endif