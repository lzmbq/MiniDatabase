/********************************************************************
	created:	2008/06/15
	created:	15:6:2008   23:02
	modified:	
	filename: 	TableManager
	file ext:	h
	author:		
	
	purpose:	数据库管理，完成对表的增删查改操作，以及数据的增删查改
*********************************************************************/
#ifndef TABLEMANAGER_H_
#define TABLEMANAGER_H_
#include "AList.h"
#include "MyTable.h"
#include "MyString.h"
#include "FileRW.h"
#include <string>
using namespace std;

class TableManager
{
private:
	// 表的集合
	AList<MyTable*>* m_DataBase;
	// 数据库名称
	string m_sDataBaseName;
	// 文件读写类
	CFileRW* m_file;
	
	string path;
	/// <summary>
    /// 从文本文件中读取数据。
    /// </summary>
	/// <returns>操作是否成功</returns>
	bool LoadTableLabels();

	/// <summary>
    /// 释放所有表的内存空间。
    /// </summary>
	/// <returns>操作是否成功</returns>
	bool Remove();
public:
	/// <summary>
    /// 根据表名创建表。
    /// </summary>
	TableManager(const string& DBName){
		m_sDataBaseName = DBName;
		m_DataBase = new AList<MyTable*>();
		path = "data\\" + DBName + "\\";
		m_file = new CFileRW((path + DBName+".txt").c_str());
		//cout << path + DBName+".txt";  测试路径是否正确
		LoadTableLabels();
	}

	/// <summary>
    /// 释放数据库空间。
    /// </summary>
	~TableManager(){
		SaveTableLabels();
		Remove();
		delete m_file;
		delete m_DataBase;
	}

	/// <summary>
    /// 保存数据库相关信息。
    /// </summary>
	/// <returns>操作是否成功</returns>
	bool SaveTableLabels() throw (const string);

	/// <summary>
    /// 设置数据库名称。
    /// </summary>
    /// <param name="name">数据库名称</param>
	/// <returns>操作是否成功</returns>
	bool setDataBaseName(string name) throw (const string);

	/// <summary>
    /// 获得数据库名称。
    /// </summary>
	/// <returns>数据库名称</returns>
	string getDataBaseName() const throw (const string);

	/// <summary>
    /// 保存表的相关数据。
    /// </summary>
	/// <param name="tableName">保存的表的名称</param>
	/// <returns>操作是否成功</returns>
	bool saveData(const string & tableName) throw (const string);

	/// <summary>
    /// 创建表。
    /// </summary>
	/// <param name="t">MyTable类的实例</param>
	/// <returns>操作是否成功</returns>
	bool createTable(MyTable& t) throw (const string);

	/// <summary>
    /// 创建表。
    /// </summary>
	/// <param name="tableName">所创建表的名称</param>
	/// <returns>操作是否成功</returns>
	bool createTable(const string & tableName) throw (const string);

	/// <summary>
    /// 根据表名获得表。
    /// </summary>
	/// <param name="tableName">所要获得的表的名称</param>
	/// <param name="temp">获得表后保存在temp中</param>
	/// <returns>操作是否成功</returns>
	bool getTable(MyTable* &temp, const string & tableName) throw (const string);

	/// <summary>
    /// 补充设置主键。
    /// </summary>
	/// <param name="columnName">所设置列的名称</param>
	/// <param name="tableName">所设置表的名称</param>
	/// <returns>操作是否成功</returns>
	bool setPrimary(const string& columnName, const string & tableName) throw (const string);

	/// <summary>
    /// 补充设置外键。
    /// </summary>
	/// <param name="columnName">所设置列的名称</param>
	/// <param name="tableName">所设置表的名称</param>
	/// <param name="fColumnName">所设置依赖的外部列的名称</param>
	/// <param name="fTableName">所设置依赖的外部表的名称</param>
	/// <returns>操作是否成功</returns>
	bool setForeign(const string& columnName, const string& fColumnName, const string & fTableName, const string & tableName) throw (const string);

	/// <summary>
    /// 查看表信息。
    /// </summary>
	/// <param name="tableName">所查看表的名称</param>
	/// <returns>操作是否成功</returns>
	bool describe(const string & tableName) throw (const string);

	/// <summary>
    /// 查看表间关系。
    /// </summary>
	/// <param name="tableName">所查看表的名称</param>
	/// <returns>操作是否成功</returns>
	bool getTableRelation(const string & tableName) throw (const string);

	/// <summary>
    /// 删除表操作。
    /// </summary>
	/// <param name="tableName">所删除表的名称</param>
	/// <returns>操作是否成功</returns>
	bool deleteTable(const string& tableName) throw (const string);

	/// <summary>
    /// 修改表操作，增加列。
    /// </summary>
	/// <param name="columnName">要增加的列的名称</param>
	/// <param name="columnType">要增加的列的类型</param>
	/// <param name="tableName">所修改表的名称</param>
	/// <returns>操作是否成功</returns>
	bool alterTable(const string& columnName, const string& columnType, const string& tableName) throw (const string);

	/// <summary>
    /// 删除列操作。
    /// </summary>
	/// <param name="columnName">所删除列的名称</param>
	/// <param name="tableName">表的名称</param>
	/// <returns>操作是否成功</returns>
	bool dropTableColumn(const string& columnName, const string& tableName) throw (const string);

	/// <summary>
    /// 插入记录操作。
    /// </summary>
	/// <param name="data">所插入的数据</param>
	/// <param name="tableName">表的名称</param>
	/// <returns>操作是否成功</returns>
	bool insertData(string data[], const string & tableName) throw (const string);

	/// <summary>
    /// 查找记录操作。
    /// </summary>
	/// <param name="comp">与关键字比较的方式</param>
	/// <param name="sql">查找的关键字</param>
	/// <param name="tableName">表的名称</param>
	/// <returns>操作是否成功</returns>
	bool selectData(LList<string>& columnList, const string& comp,const int & sql,const string & tableName) throw (const string);

	/// <summary>
    /// 查找记录操作，结果按降序排列。
    /// </summary>
	/// <param name="comp">与关键字比较的方式</param>
	/// <param name="sql">查找的关键字</param>
	/// <param name="tableName">表的名称</param>
	/// <returns>操作是否成功</returns>
	bool selectDataByDesc(LList<string>& columnList, const string& comp, const int & sql,const string & tableName) throw (const string);

	/// <summary>
    /// 查找表中所有记录。
    /// </summary>
	/// <param name="tableName">表的名称</param>
	/// <returns>操作是否成功</returns>
	bool selectData(LList<string>& columnList,const string & tableName) throw (const string);

	/// <summary>
    /// 查找表中记录。
    /// </summary>
	/// <param name="column">记录需匹配列</param>
	/// <param name="tableName">表的名称</param>
	/// <returns>操作是否成功</returns>
	bool selectData(LList<string>& columnList, const string& column, const string & tableName) throw (const string);
	
	/// <summary>
    /// 删除记录操作。
    /// </summary>
	/// <param name="comp">与关键字比较的方式</param>
	/// <param name="sql">查找的关键字</param>
	/// <param name="tableName">表的名称</param>
	/// <returns>操作是否成功</returns>
	bool deleteData(const string& comp, const int & sql,const string & tableName) throw (const string);

	/// <summary>
    /// 修改记录操作。
    /// </summary>
	/// <param name="comp">与关键字比较的方式</param>
	/// <param name="sql">查找的关键字</param>
	/// <param name="tableName">表的名称</param>
	/// <returns>操作是否成功</returns>
	bool updataData(int index, const string& columnName, const string& value, const string & tableName) throw (const string);

	/// <summary>
    /// 设置索引操作。
    /// </summary>
	/// <param name="columnName">所设置的列名</param>
	/// <param name="tableName">表的名称</param>
	/// <returns>操作是否成功</returns>
	bool setIndex(const string & columnName, const string & tableName) throw (const string);
	
	/// <summary>
    /// 查看数据库中的表。
    /// </summary>
	/// <returns>操作是否成功</returns>
	bool showTables() throw (const string);
};	
#endif