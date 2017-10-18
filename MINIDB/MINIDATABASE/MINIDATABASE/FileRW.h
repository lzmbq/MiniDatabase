/********************************************************************
	created:	2008/06/15
	created:	15:6:2008   23:02
	modified:	
	filename: 	FileRW
	file ext:	h
	author:		
	
	purpose:	对文件操作进行封装，提供文件的打开，关闭以及读写操作
*********************************************************************/
// FileRW.h: interface for the CFileRW class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILERW_H__DDE28A2C_392A_473E_A597_84CD439B0052__INCLUDED_)
#define AFX_FILERW_H__DDE28A2C_392A_473E_A597_84CD439B0052__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class CFileRW  
{
private:
	ofstream out;
	ifstream in;
	char tableName[30];
public:
	bool Open(const char&);
	bool Close(const char&);
	CFileRW() {}
	CFileRW(const char* tName);
	virtual ~CFileRW();
	
	bool SetTableName(const char* tName);
	bool IsEof(const char& t);
	string ReadStr();
	int ReadInt();
	bool WriteStr(const string& str);
	bool WriteInt(const int& num);
	string ReadRow();
	bool WriteRow(const string&);

	bool Open(const char* tName);
};

#endif // !defined(AFX_FILERW_H__DDE28A2C_392A_473E_A597_84CD439B0052__INCLUDED_)

