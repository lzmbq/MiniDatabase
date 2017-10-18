/********************************************************************
	created:	2008/06/15
	created:	15:6:2008   23:02
	modified:	
	filename: 	
	file ext:	h
	author:		
	
	purpose:	
*********************************************************************/
#ifndef LINK_H_
#define LINK_H_
#include <stdlib.h>

template <class Elem> 
class Link{
public:
	Elem element;
	Link *next;
	Link(Link*nextval = NULL)
	{
		next=nextval;
	}
	Link(const Elem&elemval, Link *nextval=null)
	{
		element=elemval; 
		next=nextval;
	}
};      

#endif