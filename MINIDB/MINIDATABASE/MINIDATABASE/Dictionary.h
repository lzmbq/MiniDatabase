/********************************************************************
	created:	2008/06/15
	created:	15:6:2008   23:02
	modified:	
	filename: 	
	file ext:	h
	author:		
	
	purpose:	
*********************************************************************/
// The Dictionary abstract class.  KEComp compares a key
#ifndef DICTIONARY_H_
#define DICTIONARY_H_
// and an element. EEComp compares two elements.  
template <class Key, class Elem, class KEComp, class EEComp>
class  Dictionary {
public:
	// Reinitialize dictionary
	virtual void clear() = 0;
	// Insert an element.  Return true if insert is
	// successful, false otherwise.
	virtual bool insert(const Elem&) = 0;
	// Remove some element matching Key.  Return true if such
	// exists, false otherwise.  If multiple entries match
	// Key, an arbitrary one is removed.
	virtual bool remove(const Key&, Elem&) = 0;
	// Remove and return an arbitrary element from dictionary.
	// Return true if some element is found, false otherwise.
	virtual bool removeAny(Elem&) = 0;
	// Return a copy of some Elem matching Key.  Return true
	// if such exists, false otherwise.  If multiple elements
	// match Key, return an arbitrary one.
	virtual bool find(const Key&, Elem&) const = 0;
	// Return the number of elements in the dictionary.
	virtual int size() = 0;
};

#endif