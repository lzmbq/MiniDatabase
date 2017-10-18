/********************************************************************
	created:	2008/06/15
	created:	15:6:2008   23:02
	modified:	
	filename: 	TableHead
	file ext:	h
	author:		
	
	purpose:	�Ա�ͷ�ĳ���ʵ�ֶԱ�ͷ�е��е���ɾ��Ĳ���
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
	LList<Column> m_pListColumn; // ����Ϣ�б�
	string m_pStrTableName; // ����
	int m_iColumnCount; // ����
	int m_iAllColumnSize; // һ�е����ݵ��ܴ�С
	
public:
	TableHead();
	bool AddColumn(const Column&);
	Column GetColmn(int);

	int GetColumnCount() const;

	bool DeleteColumn(Column& c, string columnName);

	bool SetColumnLength(int);
};

#endif 