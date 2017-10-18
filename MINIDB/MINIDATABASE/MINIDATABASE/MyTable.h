/********************************************************************
	created:	2008/06/15
	created:	15:6:2008   23:02
	modified:	
	filename: 	MyTable
	file ext:	h
	author:		
	
	purpose:	对数据实现增删查改操作
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
	string m_pStrTableName;			// 表名称
	TableHead* m_TableHead;			//
	TableBody<string> m_TableBody;	//
	Index * m_Index;	//
	int m_IndexColumn;	// 索引第几列
	CFileRW* m_file;	// 定义文件操作类
	bool m_bLoaded;		// 是否已经装载
	string m_pParent;	// 父表名列表和列名
	string path;
	string m_strDatabaseName;

	int IsTableColumn(const string& columnName); // 返回tablehead的位置，不在返回-1
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
	// 补充设置主键
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
	// 查看表信息
	bool Describe(const string& operType) throw (const string);
	int GetColumnLength() throw (const string);
	//根据属性名获得列
	Column GetColumn(const string& columnName) const throw (const string);
	//设置索引
	bool SetIndex(const string & columnName) throw (const string);
	//设置非主键索引
	bool SetStrIndex(const string & columnName) throw (const string);
	//通过索引删除数据
	bool Delete(const string&, int) throw (const string);
	//更新数据
	bool Updata(int index, const string& columnName, const string& value) throw (const string);
	//保存数据到文件中
	bool SaveData() throw (const string);
	//读取数据到文件中
	bool LoadData() throw (const string);
	// 打印表头
	void PrintTableHead() throw (const string);
	bool PrintTableHead(LList<string>& columnList, LList<int>& columnPos) throw (const string);
};
#endif