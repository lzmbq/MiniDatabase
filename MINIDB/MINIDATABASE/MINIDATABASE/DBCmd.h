/********************************************************************
	created:	2008/08/01
	created:	
	modified:	
	filename: 	
	file ext:	h
	author:		
	
	purpose:	解析数据库操作的语句
*********************************************************************/
#ifndef DBCMD_H_
#define DBCMD_H_
#include "DataBase.h"
class DBCmd
{
public:
	bool static use(string a[], int n, const DataBase& db, const TableManager*& tm) throw (const string);
};


#endif