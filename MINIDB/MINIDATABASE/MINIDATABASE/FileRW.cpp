/********************************************************************
	created:	2008/06/15
	created:	15:6:2008   23:02
	modified:	
	filename: 	FileRW
	file ext:	cpp
	author:		
	
	purpose:	对文件操作进行封装，提供文件的打开，关闭以及读写操作
*********************************************************************/
// FileRW.cpp: implementation of the CFileRW class.
//
//////////////////////////////////////////////////////////////////////

#include "FileRW.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileRW::CFileRW(const char* tName)
{
	strcpy(tableName,tName);
}

CFileRW::~CFileRW()
{
	in.close();
	out.close();
}
bool CFileRW::SetTableName(const char* tName)
{
	strcpy(tableName,tName);
	return true;
}

bool CFileRW::Open(const char& t)
{
	if(t=='i')
	{
		in.open(tableName);
		return true;
	}
	else if(t=='o')
	{
		out.open(tableName);
		return true;
	}
	return false;
}
bool CFileRW::Close(const char& t)
{
	if(t=='i')
	{
		in.close();
		return true;
	}
	else if(t=='o')
	{
		out.close();
		return true;
	}
	else 
		return false;
}
string CFileRW::ReadStr()
{
	char str[50];
	in.getline(str,50);
	return str;
}
bool CFileRW::IsEof(const char& t)
{
	if (t == 'o')
		return out.eof();
	else 
		return in.eof();
}
bool CFileRW::WriteStr(const string& str)
{
	out << str << endl;
	return true;
}
bool CFileRW::WriteInt(const int& num)
{
	out << num << endl;
	return true;
}
int CFileRW::ReadInt()
{
	int num;
	in >> num;
	char str[50];
	in.getline(str,50);
	return num;
}