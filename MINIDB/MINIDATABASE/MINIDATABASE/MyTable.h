/********************************************************************
	created:	2008/06/15
	created:	15:6:2008   23:02
	modified:	
	filename: 	MyTable
	file ext:	h
	author:		
	
	purpose:	������ʵ����ɾ��Ĳ���
*********************************************************************/
#include "stdafx.h"
#ifndef TableText_H_
#define TableText_H_
#include "TableBody.h"
#include "LList.h"
#include "Column.h"
#include "TableHead.h"
#include "AVLTree.h"
#include "Elem.h"
#include "Index.h"
#include "MyString.h"
#include "FileRW.h"
#include <string>
#include <iomanip>
using namespace std;
class MyTable
{
private:
	string m_pStrTableName;			// ������
	TableHead* m_TableHead;			//
	TableBody<string> m_TableBody;	//
	Index * m_Index;	//
	int m_IndexColumn;	// �����ڼ���
	CFileRW* m_file;	// �����ļ�������
	bool m_bLoaded;		// �Ƿ��Ѿ�װ��
	string m_pParent;	// �������б������
	string path;
	string m_strDatabaseName;

	int IsTableColumn(const string& columnName); // ����tablehead��λ�ã����ڷ���-1
public:
	MyTable()
	{
		m_TableHead = NULL;
		m_IndexColumn = 0;
		m_Index = NULL;
	}
	MyTable(const string& tableName, const string& DBName)
	{
		m_strDatabaseName = DBName;
		path = "data\\" + m_strDatabaseName + "\\";
		m_pParent = "NULL";
		m_TableHead = NULL;
		m_IndexColumn = 0;
		m_Index = new Index();
		this->SetTableName(tableName);
		m_file = new CFileRW((path + tableName+".txt").c_str());
		m_bLoaded = false;
	}
	MyTable(TableHead&,const string& tableName);
	~MyTable(){
		if (m_TableHead != NULL)
			delete m_TableHead;
		delete m_file;
		delete m_Index;
	}
	void SetTableName(const string & name) throw (const string);
	string GetTableName() const throw (const string);
	bool Insert(string data[], const int n) throw (const string);
	// ������������
	bool SetPrimary(const string& columnName);
	bool SetForeign(const string& columnName, const string& fColumnName, const string & fTableName) throw (const string);
	bool SetParentName(const string& parentName) throw (const string);
	string GetParentName() const throw (const string);
	bool AlterTable(const string& columnName, const string& columnType) throw (const string);
	bool DropTableColumn(const string& columnName) throw (const string);
	// Select
	bool Select(LList<string>& columnList, const string& comp,int sql) throw (const string);
	bool SelectByDesc(LList<string>& columnList, const string&, int) throw (const string);
	bool Select(LList<string>& columnList) throw (const string);
	bool Select(LList<string>& columnList, const string& columnName) throw (const string);
	// �鿴����Ϣ
	bool Describe(const string& operType) throw (const string);
	int GetColumnLength() throw (const string);
	//���������������
	Column GetColumn(const string& columnName) const throw (const string);
	//��������
	bool SetIndex(const string & columnName) throw (const string);
	//���÷���������
	bool SetStrIndex(const string & columnName) throw (const string);
	//ͨ������ɾ������
	bool Delete(const string&, int) throw (const string);
	//��������
	bool Updata(int index, const string& columnName, const string& value) throw (const string);
	//�������ݵ��ļ���
	bool SaveData() throw (const string);
	//��ȡ���ݵ��ļ���
	bool LoadData() throw (const string);
	// ��ӡ��ͷ
	void PrintTableHead() throw (const string);
	bool PrintTableHead(LList<string>& columnList, LList<int>& columnPos) throw (const string);
};
#endif