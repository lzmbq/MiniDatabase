/********************************************************************
	created:	2008/06/15
	created:	15:6:2008   23:02
	modified:	
	filename: 	Column
	file ext:	h
	author:		
	
	purpose:	该类为一个表提供列的属性定义
*********************************************************************/
#ifndef COLUMN_H_
#define COLUMN_H_
#include <string>

enum E_DATA_TYPE{MY_CHAR,MY_SHORT,MY_INT,MY_LONG,MY_FLOAT,MY_DOUBLE,MY_VARCHAR};
#include <iostream>
using namespace std;

class Column
{
private:
	string m_pStrColumnName;	// 列名（10字节）
	E_DATA_TYPE	m_dataType;		// 列的数据类型
	short m_sDataSize;			// 本列数据类型所占的空间
	int m_flags;				// 标识位，1为主键，2为外键，3为索引，4为缺省NULL
	string m_pStrForTableName;	// 外键相连接的表名（20字节）
	string m_pStrForColName;	// 外键相连接的列名（10字节）
public:
	Column();
	Column(string name,	int	type, short size, int flags, string pStrForTableName, string pStrForColName);
	bool setFlog(int flag);
	char getFlog() const;

	bool setColName(string name);
	string getColName() const;
	
	bool setDataSize(short size);
	short getDataSize() const;

	bool setDataType(E_DATA_TYPE type);
	E_DATA_TYPE getDataType() const;
	
	bool setStrForTableName(string pStrForTableName);
	string getStrForTableName() const;

	bool setStrForColName(string pStrForColName);
	string getStrForColName() const;
};
#endif