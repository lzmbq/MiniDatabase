/********************************************************************
	created:	2008/06/15
	created:	15:6:2008   23:02
	modified:	
	filename: 	Column
	file ext:	cpp
	author:		
	
	purpose:	该类为一个表提供列的属性定义
*********************************************************************/
#include "Column.h"

Column::Column()
{
	m_flags = 4;
	m_pStrColumnName = "";
	m_pStrForTableName = "";
	m_sDataSize = 0;
	m_pStrForColName = "";
}

Column::Column(string name,	
				int	type,		
				short size,			
				int flags,				
				string pStrForTableName,
				string pStrForColName
				)
{
	m_pStrColumnName = name;
	m_dataType = (E_DATA_TYPE)type;
	m_sDataSize = size;
	m_flags = flags;
	m_pStrForTableName = pStrForTableName;
	m_pStrForColName = pStrForColName;
}

bool Column::setFlog(int flag)
{
	this->m_flags = flag;
	return true;
}

char Column::getFlog() const
{
	return m_flags;
}

bool Column::setColName(string name)
{
	this->m_pStrColumnName = name;
//cout <<  m_pStrColumnName;
	return true;
}

string Column::getColName() const
{
	return m_pStrColumnName;
}

bool Column::setDataSize(short size)
{
	this->m_sDataSize = size;
	return true;
}

short Column::getDataSize() const
{
	return m_sDataSize;
}

bool Column::setDataType(E_DATA_TYPE type)
{
	this->m_dataType = type;
	return true;
}
E_DATA_TYPE Column::getDataType() const
{
	return m_dataType;
}


bool Column::setStrForTableName(string pStrForTableName)
{
	this->m_pStrForTableName = pStrForTableName;
	return true;
}
string Column::getStrForTableName() const
{
	return m_pStrForTableName;
}

bool Column::setStrForColName(string pStrForColName)
{
	this->m_pStrForColName = pStrForColName;
	return true;
}
string Column::getStrForColName() const
{
	return m_pStrForColName;
}