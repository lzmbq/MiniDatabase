/********************************************************************
	created:	2008/06/15
	created:	15:6:2008   23:02
	modified:	
	filename: 	
	file ext:	h
	author:		
	
	purpose:	
*********************************************************************/
#ifndef ALIST_H_
#define ALIST_H_

#include "List.h"
#include <iostream>

using namespace std;
const int DefaultListSize = 300; 

template <class Elem> 
class AList: public List<Elem>
{
private:
   int maxSize;
   int listSize;
   int fence;
   Elem* listArray;
public:
	AList(int size=DefaultListSize);
	virtual ~AList();
	void clear();
	bool insert(const Elem&);
	bool append(const Elem&); 
	bool remove(Elem&);
	void setStart();
	void setEnd();
	void prev();
	void next();
	int length() const;
	int leftLength() const;
	int rightLength() const;
	bool setPos(int Pos);
	bool getValue(Elem& ) const;
	void print() const;
	// ÄæÐò
	void reverse();
};


template <class Elem>
AList<Elem>::AList(int size=DefaultListSize)
{
	maxSize=size;
	listSize=fence=0;
	listArray=new Elem[maxSize];
} // AList()

template <class Elem>
AList<Elem>::~AList()
{
	delete [] listArray;
} // ~AList

template <class Elem>
void AList<Elem>::clear()
{
	delete [] listArray;
	listSize=fence=0;
	listArray=new Elem[maxSize];   
} // clear

template <class Elem>
void AList<Elem>::setStart()
{
	fence=0;
} // setStart

template <class Elem>
void AList<Elem>::setEnd()
{
	fence=listSize;
} // setEnd

template <class Elem>
void AList<Elem>::prev()
{
	if(fence!=0) 
		fence--;
} // prev

template <class Elem>
void AList<Elem>::next()
{
	if(fence<=listSize) 
		fence++;
} // next

template <class Elem>
int AList<Elem>::length() const
{
	return listSize;
} // length

template <class Elem>
int AList<Elem>::leftLength() const
{
	return fence;
} // leftLength

template <class Elem>
int AList<Elem>::rightLength() const
{
	return listSize-fence;
} // rightLength

template <class Elem>
bool AList<Elem>::setPos(int pos)
{
	if((pos>=0)&&(pos<=listSize))
		fence=pos;
	return (pos>=0)&&(pos<=listSize);
} // setPos

template <class Elem>
bool AList<Elem>::getValue(Elem&it) const
{
	if(rightLength()==0) 
		return false;
	else 
	{
		it=listArray[fence]; 
		return true;
	}
} // getValue

template <class Elem>
void AList<Elem>::print() const
{
	int t=0;     
	cout<<"<";
	while(t<fence)
		cout<<listArray[t++]<<" ";
	cout<<"|";
	
	while(t<listSize)
		cout<<listArray[t++]<<" "; 
	cout<<">\n";
} // print

template <class Elem> 
bool AList<Elem>:: insert(const Elem&item)
{
	if(listSize==maxSize) 
		return false;
	for (int i=listSize;i>fence;i--)
		listArray[i]=listArray[i-1];
	listArray[fence]=item;
	listSize++;
	return true;
} // insert

template <class Elem> 
bool AList<Elem>:: append(const Elem&item)
{
	if(listSize==maxSize)
		return false;
	listArray[listSize++]=item;
	return true;
} // append

template <class Elem> 
bool AList<Elem>:: remove(Elem& it)
{
	if(rightLength()==0)
		return false;
	it=listArray[fence];    
	for(int i=fence;i<listSize-1;i++)
		listArray[i]=listArray[i+1];
	listSize--;   
	return true;  
} // remove

template <class Elem>
void AList<Elem>::reverse()
{
	Elem temp;
	if (listSize%2 == 1)
		for (int i=0; i< (listSize-1)/2; i++)
		{
			temp = listArray[i];
			listArray[i] = listArray[listSize-i-1];
			listArray[listSize-i-1] = temp;
		}
	else 
	{
		for (int i=0; i< (listSize)/2; i++)
		{
			temp = listArray[i];
			listArray[i] = listArray[listSize-i-1];
			listArray[listSize-i-1] = temp;
		}	
	}
}
#endif

