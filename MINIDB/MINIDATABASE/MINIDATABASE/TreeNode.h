/********************************************************************
	created:	2008/06/15
	created:	15:6:2008   23:02
	modified:	
	filename: 	
	file ext:	h
	author:		
	
	purpose:	
*********************************************************************/
#ifndef TREENODE_H_
#define TREENODE_H_
// Binary tree node abstract class
template <class Elem> class BinNode {
public:
	// Return the node's element
	virtual Elem& val() = 0;
	// Set the node's element
	virtual void setVal(const Elem&) = 0;
	// Return the node's left child
	virtual BinNode* left() const = 0;
	// Set the node's left child
	virtual void setLeft(BinNode*) = 0;
	// Return the node's right child
	virtual BinNode* right() const = 0;
	// Set the node's right child
	virtual void setRight(BinNode*) = 0;
	// Return true iff the node is a leaf
	virtual bool isLeaf() = 0;
	//my personal preference
	virtual BinNode<Elem>* getSon(bool isLeft)const=0; 
	//my personal preference
	virtual void setSon(BinNode<Elem>* son, bool isLeft)=0;

};

// Binary tree node class
template <class Elem>
class BinNodePtr : public BinNode<Elem> {
private:
	Elem it;                     // The node's value
	BinNodePtr* lc;              // Pointer to left child
	BinNodePtr* rc;              // Pointer to right child
public:
	// Two constructors -- with and without initial values
	BinNodePtr() { 
		lc = rc = NULL; 
	}

	BinNodePtr(Elem e, BinNodePtr* l =NULL,	BinNodePtr* r =NULL){ 
		it = e; lc = l; rc = r; 
	}

	~BinNodePtr() {}             // Destructor

	Elem& val() { 
		return it; 
	}

	void setVal(const Elem& e) { 
		it = e; 
	}

	inline BinNode<Elem>* left() const { 
		return lc; 
	}

	void setLeft(BinNode<Elem>* b) {
		lc = (BinNodePtr*)b;
	}

	inline BinNode<Elem>* right() const {
		return rc; 
	}

	void setRight(BinNode<Elem>* b) { 
		rc = (BinNodePtr*)b; 
	}

	bool isLeaf() { 
		return (lc == NULL) && (rc == NULL);
	}

	BinNode<Elem>* getSon(bool isLeft)const {
		return isLeft?lc:rc;
	}
	void setSon(BinNode<Elem>* son, bool isLeft){
		isLeft?setLeft(son):setRight(son);
	}
};


template <class Elem>
class AVLNodePtr : public BinNode<Elem> 
{
protected:
	Elem it;                     // The node's value
	AVLNodePtr* lc;              // Pointer to left child
	AVLNodePtr* rc;              // Pointer to right child
	int height;
	bool inLeft;
	int address;
public:
	// Two constructors -- with and without initial values
	AVLNodePtr() { 
		lc = rc = NULL; height=1; inLeft=true; 
	}
	AVLNodePtr(Elem e, AVLNodePtr<Elem>* l =NULL,AVLNodePtr<Elem>* r =NULL, int newHeight=1,int addr = 0){ 
		it = e; 
		lc = l; 
		rc = r;
		height=newHeight; 
		inLeft=true;
		address = addr;
	}
	~AVLNodePtr() {}             // Destructor
	Elem& val() { 
		return it; 
	}
	int Addr() {
		return address;
	}
	void setVal(const Elem& e) { 
		it = e; 
	}
	BinNode<Elem>* left() const {
		return lc; 
	}
	void setLeft(BinNode<Elem>* b) {
		lc = (AVLNodePtr*)b;
	}
	inline BinNode<Elem>* right() const { 
		return rc; 
	}
	void setRight(BinNode<Elem>* b) { 
		rc = (AVLNodePtr*)b; 
	}
	bool isLeaf() {
		return (lc == NULL) && (rc == NULL); 
	}
	void setHeight(int newHeight){
		height=newHeight;
	}
	int getHeight(){
		return height;
	}
	BinNode<Elem>* getSon(bool isLeft)const {
		return isLeft?lc:rc;
	}
	bool getSide() const {
		return inLeft;
	}
	void setSide(bool isLeft){
		inLeft=isLeft;
	}
	void setSon(BinNode<Elem>* son, bool isLeft){
		isLeft?setLeft(son):setRight(son);
	}
	
};
#endif