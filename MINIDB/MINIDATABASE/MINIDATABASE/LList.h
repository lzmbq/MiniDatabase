/********************************************************************
	created:	2008/06/15
	created:	15:6:2008   23:02
	modified:	
	filename: 	
	file ext:	h
	author:		
	
	purpose:	
*********************************************************************/
#ifndef LLIST_H_
#define LLIST_H_

#include "Link.h"
#include "List.h"
#include <stdlib.h>
#include <iostream>
using namespace std;
//const int DefaultListSize;

template <class Elem>
 class LList: public List<Elem>
{
private:
	Link<Elem>*head;
	Link<Elem>*tail;
	Link<Elem>*fence;
	int leftcnt, rightcnt;
	void init();
	void removeall();     
public:
	LList();
	~LList();
	void clear();
	bool insert(const Elem&);
	bool append(const Elem&);
	bool remove(Elem&);
	void setStart();		
	void setEnd();			
	void prev();
	void next();				
	int leftLength() const;
	int rightLength() const;
	bool setPos(int Pos);
	bool getValue(Elem &it) const;
//	void print() const;
	// ÄæÐò
	void reverse();
};
template <class Elem>
void LList<Elem>::init()
{
	fence=head=tail=new Link<Elem>;
	tail->next = NULL;
	leftcnt=rightcnt=0;
} // init

template <class Elem>
void LList<Elem>::removeall()
{ 
	while(head!=NULL)
	{
		fence=head;
		head=head->next; 
		delete fence;
	}
}  // removeall

template <class Elem>
LList<Elem>::LList()
{
	init();
} // LList

template <class Elem>
LList<Elem>::~LList()
{
	removeall();
} // ~LList

template <class Elem>
void LList<Elem>::clear()
{
	removeall(); 
	init();
} // clear

template <class Elem>
void LList<Elem>::setStart()
{
	fence=head;
	rightcnt+=leftcnt;
	leftcnt=0;
} // setStart

template <class Elem>
void LList<Elem>::setEnd()
{
	fence=tail;
	leftcnt+=rightcnt;
	rightcnt=0;
}//setEnd

template <class Elem>
void LList<Elem>::next()
{
	if(fence!=tail)
	{
		fence=fence->next;
		rightcnt--; 
		leftcnt++;
	}
}//next
    
template <class Elem>
int LList<Elem>::leftLength()const
{ 
	return leftcnt;
} // leftLength
   
template <class Elem>
int LList<Elem>::rightLength() const
{
	return rightcnt;
} // rightLength

template <class Elem>
bool LList<Elem>::getValue(Elem& it) const
{
     if(rightLength()==0) 
		 return false;
     it=fence->next->element;
	 return true;  
}//getValue

template <class Elem>
bool LList<Elem>::insert(const Elem& item)
{
	fence->next=new Link<Elem>(item,fence->next);
	if(tail==fence)
	{
		tail=fence->next;
		tail->next = NULL;
	}
	rightcnt++;
	return true;
} // insert

template <class Elem>
bool LList<Elem>::append(const Elem& item)
{
	tail=tail->next=new Link<Elem>(item,NULL);
	rightcnt++;
	return true;
} // append

template <class Elem>
bool LList<Elem>::remove(Elem& it)
{
	if(fence->next == NULL) 
	   return false;
	it=fence->next->element;
	Link<Elem>* ltemp=fence->next;
	fence->next=ltemp->next;
	if(tail==ltemp) 
	   tail=fence;
	delete ltemp;
	rightcnt--;
	return true;
} // remove

template <class Elem>
void LList<Elem>::prev()
{
	Link<Elem> * temp=head;
	if (fence==head) 
		return;
	while(temp->next!=fence)
		 temp=temp->next;
	fence=temp;
	leftcnt--; 
	rightcnt++;
} // prev

template <class Elem>
bool LList<Elem>::setPos(int pos)
{
	if((pos<0)||(pos>(rightcnt+leftcnt))) 
		return false;
	setStart();
	for(int i=0;i<pos;i++)
		next();   
	return true;
} // setPos


/*template <class Elem>
void LList<Elem>::print() const
{
	Link<Elem>* temp=head;
	cout << "<";
	while(temp != fence)
	{
		cout<< temp->next->element <<" ";
		temp=temp->next;
	}//while
	cout<< " | ";
	while(temp->next != NULL)
	{
		cout<< temp->next->element <<" ";
		temp = temp->next;
	}//while
	cout<<">\n";
} // print
*/
template <class Elem>
void LList<Elem>::reverse()
{
	Link<Elem>* p = NULL;
	Link<Elem>* q = NULL;
	p = head->next;
	while (p->next != NULL)
	{
		q = p->next;
		p = q->next;
		q->next = head->next;
		head->next = q;	
	}
	tail = p;
}
#endif