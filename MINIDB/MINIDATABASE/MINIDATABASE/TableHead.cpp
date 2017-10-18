/********************************************************************
	created:	2008/06/15
	created:	15:6:2008   23:02
	modified:	
	filename: 	TableHead
	file ext:	cpp
	author:		
	
	purpose:	对表头的抽象，实现对表头中的列的增删查改操作
*********************************************************************/
#include "TableHead.h"


TableHead::TableHead()
{
	m_pStrTableName = "";
	m_iColumnCount = 0; 
//	cout <<m_iColumnCount;
	m_iAllColumnSize = 0;
}


bool TableHead::AddColumn(const Column& c)
{
	this->m_pListColumn.append(c);
	m_iColumnCount++;
	return true;
}

bool TableHead::DeleteColumn(Column& c, string columnName)
{
	Column temp;
	int i = 0;
	m_pListColumn.setStart();
	int length = m_pListColumn.rightLength();
	for (; i < length; i++)
	{
		m_pListColumn.getValue(temp);
		if (columnName == temp.getColName())
			break;
		m_pListColumn.next();
	}
	this->m_pListColumn.setPos(i);
	this->m_pListColumn.remove(c);
	m_iColumnCount--;
	return true;
}


Column TableHead::GetColmn(int i)
{
	Column temp;
	this->m_pListColumn.setPos(i);
	this->m_pListColumn.getValue(temp);
	return temp;
}

int TableHead::GetColumnCount() const
{
	return this->m_iColumnCount;
}

bool TableHead::SetColumnLength(int length)
{
	this->m_iColumnCount = length;
	return true;
}