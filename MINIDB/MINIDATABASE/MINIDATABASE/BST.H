/********************************************************************
	created:	2008/06/15
	created:	15:6:2008   23:02
	modified:	
	filename: 	
	file ext:	h
	author:		
	
	purpose:	
*********************************************************************/
#ifndef BST_H_
#define BST_H_
#include "dictionary.h"
#include <stdlib.h>
#include "TreeNode.h"

// Binary Search Tree implementation for the Dictionary ADT
template <class Key, class Elem, class KEComp, class EEComp>
class BST : public Dictionary<Key, Elem, KEComp, EEComp> {
protected:
	BinNode<Elem>* root;   // Root of the BST
	int nodecount;         // Number of nodes in the BST
	// Private "helper" functions
	void clearhelp(BinNode<Elem>*);
	BinNode<Elem>* inserthelp(BinNode<Elem>*, const Elem&);
	BinNode<Elem>* deletemin(BinNode<Elem>*, BinNode<Elem>*&);
	BinNode<Elem>* removehelp(BinNode<Elem>*, const Key&, BinNode<Elem>*&);
	bool findhelp(BinNode<Elem>*, const Key&, Elem&) const;
	void printhelp(BinNode<Elem>*, int) const;
public:
	BST() { 
		root = NULL; nodecount = 0;
	}  // Constructor

	~BST() {
		clearhelp(root); 
	}   // Destructor
	
	void clear(){ 
		clearhelp(root); root = NULL; nodecount = 0; 
	}

	bool insert(const Elem& e) {
		root = inserthelp(root, e);
		nodecount++;
		return true;
	}

	bool remove(const Key& K, Elem& e) {
		BinNode<Elem>* t = NULL;
		root = removehelp(root, K, t);
		if (t == NULL) 
			return false;  // Nothing found
		e = t->val();
		nodecount--;
		delete t;
		return true;
	}

	bool removeAny(Elem& e) { // Delete min value
		if (root == NULL) 
			return false; // Empty tree
		BinNode<Elem>* t;
		root = deletemin(root, t);
		e = t->val();
		delete t;
		nodecount--;
		return true;
	}

	bool find(const Key& K, Elem& e) const{	
		return findhelp(root, K, e); 
	}
	int size() {
		return nodecount;
	}
	void print() const {
		if (root == NULL) 
			cout << "The BST is empty.\n";
		else printhelp(root, 0);
	}
};

template <class Key, class Elem, class KEComp, class EEComp>
void BST<Key, Elem, KEComp, EEComp>::clearhelp(BinNode<Elem>* subroot) 
{
	if (subroot == NULL) 
		return;
	clearhelp(subroot->left());
	clearhelp(subroot->right());
	delete subroot;
}

template <class Key, class Elem, class KEComp, class EEComp>
BinNode<Elem>* BST<Key, Elem, KEComp, EEComp>::inserthelp(BinNode<Elem>* subroot, const Elem& val)
{
	if (subroot == NULL)            // Empty tree: create node
		return (new BinNodePtr<Elem>(val, NULL, NULL));
	if (EEComp::lt(val, subroot->val())) // Insert on left
		subroot->setLeft(inserthelp(subroot->left(), val));
	else 
		subroot->setRight(inserthelp(subroot->right(), val));
	return subroot;  // Return subtree with node inserted
}

template <class Key, class Elem, class KEComp, class EEComp>
BinNode<Elem>* BST<Key, Elem, KEComp, EEComp>::deletemin(BinNode<Elem>* subroot, BinNode<Elem>*& min) 
{
	if (subroot->left() == NULL) { // Found min
		min = subroot;
		return subroot->right();
	}
	else {                         // Continue left
		subroot->setLeft(deletemin(subroot->left(), min));
		return subroot;
	}
}

template <class Key, class Elem, class KEComp, class EEComp>
BinNode<Elem>* BST<Key, Elem, KEComp, EEComp>::removehelp(BinNode<Elem>* subroot, 
														  const Key& K, BinNode<Elem>*& t) {
	if (subroot == NULL) 
		return NULL; // Val is not in tree
	else if (KEComp::lt(K, subroot->val())) // Check left
		subroot->setLeft(removehelp(subroot->left(), K, t));
	else if (KEComp::gt(K, subroot->val())) // Check right
		subroot->setRight(removehelp(subroot->right(), K, t));
	else {                           // Found it: remove it
		BinNode<Elem>* temp;
		t = subroot;
		if (subroot->left() == NULL)       // Only a right child
			subroot = subroot->right();      //  so point to right
		else if (subroot->right() == NULL) // Only a left child
			subroot = subroot->left();       //  so point to left
		else {                    // Both children are non-empty
			subroot->setRight(deletemin(subroot->right(), temp));
			Elem te = subroot->val();
			subroot->setVal(temp->val());
			temp->setVal(te);
			t = temp;
		}
	}
	return subroot;
}

template <class Key, class Elem, class KEComp, class EEComp>
bool BST<Key, Elem, KEComp, EEComp>:: findhelp(BinNode<Elem>* subroot, const Key& K, Elem& e) const {
	if (subroot == NULL) 
		return false;         // Empty tree
	else if (KEComp::lt(K, subroot->val()))    // Check left
		return findhelp(subroot->left(), K, e);
	else if (KEComp::gt(K, subroot->val()))    // Check right
		return findhelp(subroot->right(), K, e);
	else {
		e = subroot->val(); 
		return true; 
	} // Found it
}

template <class Key, class Elem, class KEComp, class EEComp>
void BST<Key, Elem, KEComp, EEComp>::printhelp(BinNode<Elem>* subroot, int level) const {
	if (subroot == NULL) return;          // Empty tree
		printhelp(subroot->left(), level+1);  // Do left subtree
	for (int i=0; i<level; i++)           // Indent to level
		cout << "  ";
	cout << subroot->val() << "\n";       // Print node value
	printhelp(subroot->right(), level+1); // Do right subtree
}
#endif