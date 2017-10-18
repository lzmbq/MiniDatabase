/********************************************************************
	created:	2008/06/15
	created:	15:6:2008   23:02
	modified:	
	filename: 	MyString
	file ext:	h
	author:		
	
	purpose:	该类完成字符串的转换操作，类型检查
*********************************************************************/
#ifndef MYSTRING_H_
#define MYSTRING_H_
#include <string>
#include <iostream>
#include "AStack.h"
#pragma warning( disable : 4290 )
using namespace std;
class MyString
{
private:
public:
	bool static Analyse(const string& allStr,string& s, int pos) throw (const string);
	string static Create(const string s[], int) throw (const string);
	int static StringToInt(const string& str) throw (const string);
	string static IntToString(const int& num) throw (const string);

	void static IsChar(const string& str) throw (const string);
	void static IsShort(const string& str) throw (const string);
	void static IsInt(const string& str) throw (const string);
	void static IsLong(const string& str) throw (const string);
	void static IsVarChar(const string& str, const int& length) throw (const string);
};
#endif