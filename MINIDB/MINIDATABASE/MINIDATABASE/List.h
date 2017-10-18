/********************************************************************
	created:	2008/06/15
	created:	15:6:2008   23:02
	modified:	
	filename: 	
	file ext:	h
	author:		
	
	purpose:	
*********************************************************************/
#ifndef LIST_H_
#define LIST_H_

template <class Elem> 
class List
{
public:
	virtual void clear()=0;
	virtual bool insert(const Elem&)=0;
	virtual bool append(const Elem&)=0;
	virtual bool remove(Elem&)=0;
	virtual void setStart()=0;
	virtual void setEnd()=0;
	virtual void prev()=0;
	virtual void next()=0;
	virtual int leftLength() const=0;
	virtual int rightLength() const=0;
	virtual bool setPos(int Pos)=0;
	virtual bool getValue(Elem&) const=0;
//	virtual void print() const=0;
};

#endif