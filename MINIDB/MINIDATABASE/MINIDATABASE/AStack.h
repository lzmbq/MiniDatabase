#ifndef ASTACK_H_
#define ASTACK_H_
template <class Elem> class AStack
{
private:
	int size;
	int top;
	Elem *listArray;
public:
	AStack(int sz=50)
	{
		size=sz;  
		top=0;  
		listArray=new Elem[size];
	}//
	~AStack() {
		delete [] listArray;
	}//
	void  clear() {
		top=0;
	} //
	bool push(const Elem& item){
		if(top==size) return false;
		else{
			listArray[top++]=item; 
			return true;
		}
	}//
	bool pop(Elem &it){
		if(top==0) return false;
		else {
			it=listArray[--top];  
			return true;
		}
	}//
	bool topValue(Elem &it) const{
		if(top==0) return false;
		else {
			it=listArray[top-1]; 
			return true;
		}
	}//
	int length() const {
		return top;
	}//
};
#endif