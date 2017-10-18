/********************************************************************
	created:	2008/06/15
	created:	15:6:2008   23:02
	modified:	
	filename: 	TableHead
	file ext:	h
	author:		
	
	purpose:	对表头的抽象，实现对表头中的列的增删查改操作
*********************************************************************/
#ifndef TABLEHEAD_H_
#define TABLEHEAD_H_
#include "LList.h"
#include "Column.h"
#include <string>
using namespace std;
class TableHead
{
private:
	LList<Column> m_pListColumn; // 列信息列表
	string m_pStrTableName; // 表名
	int m_iColumnCount; // 列数
	int m_iAllColumnSize; // 一行的数据的总大小
	
public:
	TableHead();
	bool AddColumn(const Column&);
	Column GetColmn(int);

	int GetColumnCount() const;

	bool DeleteColumn(Column& c, string columnName);

	bool SetColumnLength(int);
};

#endif 