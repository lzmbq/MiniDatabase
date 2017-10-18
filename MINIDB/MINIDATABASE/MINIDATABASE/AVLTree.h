/********************************************************************
	created:	2008/06/15
	created:	15:6:2008   23:02
	modified:	
	filename: 	
	file ext:	h
	author:		
	
	purpose:	
*********************************************************************/
#ifndef AVLTREE_H_
#define AVLTREE_H_
#include "BST.h"
#include "LList.h"
template<class Elem>
struct Descriptor
{
	BinNode<Elem>* parent;
	bool isRoot;
	bool isLeft;
	bool isSingle;
	bool left2right;
};


template<class Key, class Elem, class KEComp, class EEComp>
class AVL: public BST<Key, Elem, KEComp, EEComp>
{
protected:
//	BinNode<Elem>* startPtr;
	void clearhelp(BinNode<Elem>*);
	BinNode<Elem>* inserthelp(BinNode<Elem>*, const Elem&,const int& addr);
	BinNode<Elem>* removehelp(BinNode<Elem>*, const Key&,
							BinNode<Elem>*&);
	bool findhelp(BinNode<Elem>*, const Key&, Elem&) const;
	void printhelp(BinNode<Elem>*, int) const;
	void updateHeight(BinNode<Elem>*& subroot);
	int  getFactor(BinNode<Elem>* subroot);
	void adjust(BinNode<Elem>*& subroot, bool isRoot);
	int getTreeHeight(BinNode<Elem>* subroot);
	void adjustHeight(BinNode<Elem>* subroot);
	BinNode<Elem>* singleRotate(BinNode<Elem>* parent, bool isRoot, bool left2right);
	BinNode<Elem>* doubleRotate(BinNode<Elem>* parent, bool isRoot, bool left2right);
	void checkDir(BinNode<Elem>* subroot, bool& isSingle, bool& left2right);
	BinNode<Elem>* doDouble(BinNode<Elem>* oldRoot, bool left2right);
	
	bool findSetLessHelp(BinNode<Elem>* subroot, const Key& K, BinNode<Elem>* &temp);
	bool findSetGreaterHelp(BinNode<Elem>* subroot, const Key& K, BinNode<Elem>* &temp);
	void GreaterInOrder(BinNode<Elem>* t,const Key& K, LList<Elem>*& set);
	void LessInOrder(BinNode<Elem>* t,const Key& K, LList<Elem>*& set);
public:
	AVL() { root = NULL; nodecount = 0; }  // Constructor
	~AVL() { clearhelp(root); root=NULL; }            // Destructor
	bool insert(const Elem& e,const int& addr)
	{		
		root = inserthelp(root, e, addr);
		nodecount++;
		return true;
	}
	bool remove(const Key& k, BinNode<Elem>*& t)
	{
		root = removehelp(root,k, t);
		nodecount--;
		return true;
	}
	bool find(const Key& K, Elem& e) const{	
		return findhelp(root, K, e); 
	}
	//范围查找
	bool findSet(const string& comp, const Key& K, LList<Elem>*& set)
	{
		BinNode<Elem>* temp = NULL;
		if (comp == "less")
		{
			LessInOrder(root,K ,set);
			return true;
		}
		else if (comp == "greater")
		{
			GreaterInOrder(root,K, set);
			return true;
		}

		return false;
	}
};

//do not use recursive!!!!!
template <class Key, class Elem, class KEComp, class EEComp>
int AVL<Key, Elem, KEComp, EEComp>::getTreeHeight(BinNode<Elem>* subroot)
{
	AVLNodePtr<Elem>* ptr, *l, *r;
	int newHeight, lHeight, rHeight;//, factor;//, sonFactor;

	if (subroot==NULL)
	{
		return 0;
	}
	
	ptr=(AVLNodePtr<Elem>*)subroot;
	l=(AVLNodePtr<Elem>*)ptr->left();
	r=(AVLNodePtr<Elem>*)ptr->right();	
	if (l==NULL)
	{
		lHeight=0;
	}
	else
	{
		lHeight=l->getHeight();
	}
	if (r==NULL)
	{
		rHeight=0;
	}
	else
	{
		rHeight=r->getHeight();
	}
	newHeight=1+(lHeight>rHeight?lHeight:rHeight);
	return newHeight;
}

template <class Key, class Elem, class KEComp, class EEComp>
void AVL<Key, Elem, KEComp, EEComp>::adjustHeight(BinNode<Elem>* subroot)
{//高度变化时，从新给subroot节点的高度赋值
	int height;
	if (subroot==NULL)
	{
		return;
	}
	height=getTreeHeight(subroot);
	((AVLNodePtr<Elem>*)(subroot))->setHeight(height);
}

template <class Key, class Elem, class KEComp, class EEComp>
BinNode<Elem>* AVL<Key, Elem, KEComp, EEComp>::doDouble(BinNode<Elem>* oldRoot, 
														bool left2right)
{
	BinNode<Elem> *small, *mid, *big,*t1,*t2,*t3,*t4;
	if (left2right)
	{
		big=oldRoot;//the root;
		small=oldRoot->left();
		mid=small->right();
		t1=small->left();
		t2=mid->left();
		t3=mid->right();
		t4=big->right();
	}
	else
	{
		small=oldRoot;
		big=small->right();
		mid=big->left();
		t1=small->left();
		t2=mid->left();
		t3=mid->right();
		t4=big->right();
	}
	mid->setLeft(small);
	mid->setRight(big);
	small->setLeft(t1);
	small->setRight(t2);
	big->setLeft(t3);
	big->setRight(t4);
	adjustHeight(small);
	adjustHeight(big);
	adjustHeight(mid);
	return mid;
}

template <class Key, class Elem, class KEComp, class EEComp>
BinNode<Elem>* AVL<Key, Elem, KEComp, EEComp>::doubleRotate(BinNode<Elem>* parent,
	bool isRoot, bool left2right)
{
	BinNode<Elem>* oldRoot;
	bool isLeft;
		
	if (isRoot)
	{
		oldRoot=parent;
		root=doDouble(oldRoot, left2right);
		
		return root;//because we need parent return as real root
	}
	else
	{
		isLeft=((AVLNodePtr<Elem>*)parent)->getSide();
		oldRoot=parent->getSon(isLeft);
		parent->setSon(doDouble(oldRoot, left2right), isLeft);
		adjustHeight(parent);
		return parent;
	}
}


//if isRoot, we don't need isLeft, it is useful when it is not root and 
//we need to know which son it is in
template <class Key, class Elem, class KEComp, class EEComp>
BinNode<Elem>* AVL<Key, Elem, KEComp, EEComp>::singleRotate(BinNode<Elem>* parent,
	bool isRoot, bool left2right)
{
	BinNode<Elem>* oldRoot=parent, *son, *t1;
	bool isLeft=((AVLNodePtr<Elem>*)parent)->getSide();
	
	if (isRoot)
	{		
		son=parent->getSon(isLeft);
		t1=son->getSon(!left2right);
		son->setSon(parent, !left2right);
		parent->setSon(t1, left2right);
		//because parent is at lower level now, we need adjust parent first!!!
		adjustHeight(parent);//sequence is VERY IMPORTANT!
		adjustHeight(son);//sequence is VERY IMPORTANT!
		
		root=son;
		return son;//because now, we need return son as parent;
	}
	else
	{
		//for non-root rotation, parent doesn't change!!!!!
		//it is now very concise!!
		oldRoot=parent->getSon(isLeft);
		son=oldRoot->getSon(left2right);//this is the trick!
		t1=son->getSon(!left2right);
		parent->setSon(son, isLeft);
		oldRoot->setSon(t1, left2right);
		son->setSon(oldRoot, !left2right);
		//sequence is very important!!!
		adjustHeight(oldRoot);
		adjustHeight(son);
		adjustHeight(parent);//adjust sequence: from low to high!!!
		return parent;
	}
	
}

//check the direction of rotation by returning value in reference
template<class Key, class Elem, class KEComp, class EEComp>
void AVL<Key, Elem, KEComp, EEComp>::checkDir(BinNode<Elem>* subroot, 
											  bool& isSingle, bool& left2right)
{//isSingle判断是否是单旋转，left2right判断是平衡因子的正负
	BinNode<Elem>* son;
	int parentFactor, sonFactor;
	bool isLeft;
	isLeft=((AVLNodePtr<Elem>*)subroot)->getSide();
	son=subroot->getSon(isLeft);
	parentFactor=getFactor(subroot);
	sonFactor=getFactor(son);
	isSingle=parentFactor*sonFactor>0;//same sign
	left2right=parentFactor>0;
}

//if isroot, isLeft will be ignored.
template <class Key, class Elem, class KEComp, class EEComp>
void AVL<Key, Elem, KEComp, EEComp>::adjust(BinNode<Elem>*& subroot, bool isRoot)
{
	BinNode<Elem>* temp;
	bool isSingle, left2right, isLeft;
	if (isRoot)
	{
		temp=subroot;
	}
	else
	{
		//use its son to check
		isLeft=((AVLNodePtr<Elem>*)subroot)->getSide();
		temp=subroot->getSon(isLeft);
	}

	checkDir(temp, isSingle, left2right);
	if (isSingle)
	{
		//it helps reading and for singleRotate isLeft is ignored when it is isRoot
		subroot=singleRotate(subroot, isRoot, left2right);
	}
	else
	{
		subroot=doubleRotate(subroot, isRoot, left2right);
	}
}


template <class Key, class Elem, class KEComp, class EEComp>
int AVL<Key, Elem, KEComp, EEComp>::getFactor(BinNode<Elem>* subroot)
{//获得左子树减右子树的差
	int lHeight, rHeight;
	AVLNodePtr<Elem>* ptr, *l, *r;
	if (subroot==NULL)
	{
		return 0;
	}
	ptr=(AVLNodePtr<Elem>*)subroot;
	l=(AVLNodePtr<Elem>*)(ptr->left());
	r=(AVLNodePtr<Elem>*)(ptr->right());
	if (l==NULL)
	{
		lHeight=0;
	}
	else
	{
		lHeight= l->getHeight();
	}
	if (r==NULL)
	{
		rHeight=0;
	}
	else
	{
		rHeight=r->getHeight();
	}
	return lHeight-rHeight;
}

template <class Key, class Elem, class KEComp, class EEComp>
void AVL<Key, Elem, KEComp, EEComp>::updateHeight(BinNode<Elem>*& subroot)
{//进行旋转
	int factor, sonFactor;
	bool isLeft;
	BinNode<Elem> *son;
	if (subroot==NULL)
	{
		return;
	}
	
	adjustHeight(subroot);

	factor=getFactor(subroot);

	isLeft=((AVLNodePtr<Elem>*)subroot)->getSide();
	son=subroot->getSon(isLeft);
	sonFactor=getFactor(son);
	//first situation: the first 2/-2 we meet from bottom-up
	if ((factor==2||factor==-2)&&subroot==root)
	{
		//a special case!!! as we search from bottom up
		//we may wait to adjust until we reach its father
		//the father happens to be root. But it is not a
		//root adjustment!!!
		if (sonFactor==1||sonFactor==-1)
		{
			adjust(subroot, true);
		}
		else
		{
			adjust(subroot, false);
		}				
	}
	else
	{
		
		if (sonFactor==2||sonFactor==-2)
		{
			adjust(subroot, false);
		}
	}
}




template <class Key, class Elem, class KEComp, class EEComp>
BinNode<Elem>* AVL<Key, Elem, KEComp, EEComp>::inserthelp(BinNode<Elem>* subroot, 
														  const Elem& val, const int& addr)
{
	if (subroot == NULL)            // Empty tree: create node
	{
		return (new AVLNodePtr<Elem>(val, NULL, NULL, 1,addr));
	}
	if (EEComp::lt(val, subroot->val())) // Insert on left
	{
		((AVLNodePtr<Elem>*)subroot)->setSide(true);
		subroot->setLeft(inserthelp(subroot->left(), val, addr));
		updateHeight(subroot);
	}
	else 
	{
		((AVLNodePtr<Elem>*)subroot)->setSide(false);
		subroot->setRight(inserthelp(subroot->right(), val, addr));
		updateHeight(subroot);
	}
	return subroot;  // Return subtree with node inserted
}


template <class Key, class Elem, class KEComp, class EEComp>
void AVL<Key, Elem, KEComp, EEComp>::clearhelp(BinNode<Elem>* subroot) 
{
	if (subroot == NULL)
	{
		return;
	}
	clearhelp(subroot->left());
	clearhelp(subroot->right());
	delete subroot;	
}

template<class Key, class Elem, class KEComp, class EEComp>
BinNode<Elem>* AVL<Key, Elem, KEComp, EEComp>::removehelp(BinNode<Elem>* subroot, const Key& key, BinNode<Elem>*& elem)
{

	BST::removehelp(subroot, key, elem);
	updateHeight(subroot);
	return subroot;
}
template<class Key, class Elem, class KEComp, class EEComp>
bool AVL<Key, Elem, KEComp, EEComp>::findhelp(BinNode<Elem>* subroot, const Key& K, Elem& e) const
{
	if (subroot == NULL) 
		return false;         // Empty tree
	else if (KEComp::lt(K, subroot->val()))    // Check left
		return findhelp(subroot->left(), K, e);
	else if (KEComp::gt(K, subroot->val()))    // Check right
		return findhelp(subroot->right(), K, e);
	else {
		e = ((AVLNodePtr<Elem>*)subroot)->Addr(); 
		return true; 
	} // Found it
}
template<class Key, class Elem, class KEComp, class EEComp>
bool AVL<Key, Elem, KEComp, EEComp>::findSetLessHelp(BinNode<Elem>* subroot, const Key& K, BinNode<Elem>* &temp)
{//范围查找
	if (subroot == NULL) 
	{
		return false;         // Empty tree
	}
	if(KEComp::lt(subroot->val(), K))
	{
		temp = (AVLNodePtr<Elem>*)subroot; 
		return true; 
	} // Found it
	else
	{
		return findSetLessHelp(subroot->left(), K, temp);
	}
}

template<class Key, class Elem, class KEComp, class EEComp>
bool AVL<Key, Elem, KEComp, EEComp>::findSetGreaterHelp(BinNode<Elem>* subroot, const Key& K, BinNode<Elem>* &temp)
{//范围查找
	if (subroot == NULL) 
	{
		return false;         // Empty tree
	}
	if(KEComp::gt(subroot->val(), K))
	{
		temp = (AVLNodePtr<Elem>*)subroot; 
		return true; 
	} // Found it
	else
	{
		return findSetGreaterHelp(subroot->right(), K, temp);
	}
}
template<class Key, class Elem, class KEComp, class EEComp>
void AVL<Key, Elem, KEComp, EEComp>::LessInOrder(BinNode<Elem>* t,const Key& K, LList<Elem>*& set)
{//前序遍历
	if (t)
	{
		Elem e = ((AVLNodePtr<Elem>*)t)->Addr();
		LessInOrder(t->right(), K,set);
		if (((AVLNodePtr<Elem>*)t)->val() < K)
			set->insert(e);
		LessInOrder(t->left(), K, set);
	}
}
template<class Key, class Elem, class KEComp, class EEComp>
void AVL<Key, Elem, KEComp, EEComp>::GreaterInOrder(BinNode<Elem>* t,const Key& K, LList<Elem>*& set)
{//前序遍历
	if (t)
	{
		Elem e = ((AVLNodePtr<Elem>*)t)->Addr();
		GreaterInOrder(t->right(), K,set);
		if (((AVLNodePtr<Elem>*)t)->val() > K)
			set->insert(e);
		GreaterInOrder(t->left(), K, set);
	}
}
#endif