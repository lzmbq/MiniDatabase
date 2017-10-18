/********************************************************************
	created:	2008/06/15
	created:	15:6:2008   23:02
	modified:	
	filename: 	Column
	file ext:	h
	author:		
	
	purpose:	����Ϊһ�����ṩ�е����Զ���
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
	string m_pStrColumnName;	// ������10�ֽڣ�
	E_DATA_TYPE	m_dataType;		// �е���������
	short m_sDataSize;			// ��������������ռ�Ŀռ�
	int m_flags;				// ��ʶλ��1Ϊ������2Ϊ�����3Ϊ������4ΪȱʡNULL
	string m_pStrForTableName;	// ��������ӵı�����20�ֽڣ�
	string m_pStrForColName;	// ��������ӵ�������10�ֽڣ�
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