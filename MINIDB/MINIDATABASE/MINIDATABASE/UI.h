/********************************************************************
	created:	2008/06/15
	created:	15:6:2008   23:02
	modified:	
	filename: 	
	file ext:	h
	author:		
	
	purpose:	����SQL��� 
*********************************************************************/
#ifndef UI_H_
#define UI_H_
#include "DataBase.h"
#include "TableManager.h"
#include "MyString.h"
#include "LList.h"
class UI
{
private:
	bool static isSelectDB(TableManager*& tm) throw (const string);
public:
	// use [databaseName];
	bool static use(string a[], int n, TableManager*& tm, DataBase& db) throw (const string);
	// select database;
	// select [columnName] from [tablename] where [column] [<|>|=] [index] order by [asc|desc];
	// select [columnName] from [tablename] order by [asc|desc];
	bool static select(string a[], int n, TableManager*& tm, DataBase& db) throw (const string);
	// delete from [tablename] where [column] [<|>|=] [index] ;
	bool static Delete(string a[], int n, TableManager*& tm) throw (const string);
	// insert into [tablename] ( A B C ) ;
	bool static insert(string a[], int n, TableManager*& tm) throw (const string);
	// show tables ;
	// show databases;
	bool static show(string a[], int n, TableManager*& tm, DataBase& db) throw (const string);
	// drop [tablename] ;
	// drop database [dbName];
	bool static drop(string a[], int n, TableManager*& tm, DataBase& db) throw (const string);
	// alter [tablename] add [columnname] [datatype] ;
	// alter [tablename] drop [columnname] ;
	// alter [tablename] add primary key [columnname] ;
	// alter [tablename] add foreign key [ftablename] [fcolumnname] ;
	bool static alter(string a[], int n, TableManager*& tm) throw (const string);
	// create database [DBName];
	// create table [tablename] ;
	// create index [tablename] [columnname] ;
	bool static create(string a[], int n, TableManager*& tm, DataBase& db) throw (const string);
	// update [tablename] set [columnname] = [value] where [primaryKey] = [index] ;
	bool static update(string a[], int n, TableManager*& tm) throw (const string);
	// describe [tablename] ;
	// describe [tablename] table relation ;
	bool static describe(string a[], int n, TableManager*& tm) throw (const string);
	// save ;
	// save [tablename];
	bool static save(string a[], int n, TableManager*& tm) throw (const string);
};
bool UI::isSelectDB(TableManager*& tm)
{
	if (tm == NULL)
	{
		string e = "���� DBCmd:��û��ѡ�����ݿ⣡";
		throw e;
	}
	return true;
}
// use [databaseName];
bool UI::use(string a[], int n, TableManager*& tm, DataBase& db)
{
	if(a[1] != "" && a[2] == "")
	{
		TableManager* temp;
		bool isExist = false;
		db.m_db.setStart();
		int length = db.m_db.rightLength();
		for (int i = 0; i < length; i++)
		{
			db.m_db.getValue(temp);
			if (temp->getDataBaseName() == a[1])
			{
				tm = temp;
				cout << "���ݿ��Ѹı䣡" << endl;
				isExist = true;
				break;
			}
			db.m_db.next();
		}
		if (isExist == false)
		{
			string e = "���� DBCmd:'" + a[1] + "'���ݿⲻ���ڣ�";
			throw e;
		}
		return true;
	}
	else
	{
		string e = "���� DBCmd:'" + a[1] + "'���������﷨����";
		throw e;
	}
}

// select [columnName] from [tablename] where [column] [<|>|=] [index] order by [asc|desc];
// select [columnName] from [tablename] order by [asc|desc];
bool UI::select(string a[], int n, TableManager*& tm, DataBase& db)
{
	if (a[1] == "database" && a[2] =="")
	{
		cout << "DataBase:" << endl;
		if (tm == NULL)
			cout << "NULL" << endl;
		else
			cout << tm->getDataBaseName() << endl;
		cout << "�����ɹ���" << endl;
		return true;
	}
		

	isSelectDB(tm);
	MyTable* temp;
	LList<string> columnList;
	int i = 1;
	while (a[i] != "from")
	{
		columnList.append(a[i]);
		i++;
		if (i > 18)
		{
			string e = "���� B0020:SQL��ѯ�����δ����'from'�ؼ��֣�";
			throw e;
		}
	}
	string tableName = a[i+1];

	string columnName, comp;
	int key;
	tm->getTable(temp, tableName);
	
	if (a[i+2] == "where")
	{
		columnName = a[i+3];
		
		if (temp->GetColumn(columnName).getFlog() == 1)
		{
			comp = a[i+4];
			key = MyString::StringToInt(a[i+5]);
			if (comp == "<")
				comp = "less";
			else if (comp == "=")
				comp = "equal";
			else if (comp == ">")
				comp = "greater";
			else
			{
				string e = "���� B0021:'" + comp + "'������Ч���߼��������";
				throw e;
			}
			if (a[i+6] == "order" && a[i+7] == "by")
			{
				if (a[i+8] == "desc")
					tm->selectDataByDesc(columnList, comp, key, tableName);	// �����������в���
				else if (a[i+8] == "desc" || a[i+8] == "asc")
					tm->selectData(columnList, comp, key, tableName);	// �����������в���
				else
				{
					string e = "���� B0022:'" + a[i+8] + "'Ϊδ֪��ʶ����SQL�﷨����";
					throw e;
				}
			}
			else if (a[i+6] != "" || a[i+7] != "")
			{
				string e = "���� B0023:'" + a[i+6] + "'��'" + a[i+7] + "'��������SQL�﷨����";
				throw e;
			}
			else
				tm->selectData(columnList, comp, key, tableName);
			return true;
		}
		else if (temp->GetColumn(columnName).getFlog() == 3)
		{
			tm->selectData(columnList, a[i+5] , tableName);			// ���ݷ�������hash���в���
			return true;
		}
		else
		{
			string e = "���� B0024:'" + temp->GetColumn(columnName).getColName() + "'���������������������޷����в��ң�";
			throw e;
		}
		
	}
	else if (a[i+2] == "")
	{
		if (a[10] == "asc" || a[10] == "desc")
		{
			//
			// TODO:���ұ�����������������
			//
		}
		tm->selectData(columnList, tableName);//	���ұ�����������
	}
	else
	{
		string e = "���� B0025:'" + a[i+2] + "'��������SQL�﷨����";
		throw e;
	}
	return false;
}

// delete from [tablename] where [column] [<|>|=] [index] ; 
bool UI::Delete(string a[], int n, TableManager*& tm)
{
	isSelectDB(tm);

	string tableName = a[2];
	string columnName, comp;
	int key;
	if (a[1] == "from")
	{
		if (a[3] == "where")
		{
			columnName = a[4];
			comp = a[5];
			key = MyString::StringToInt(a[6]);
			if (comp == "<")
				comp = "less";
			else if (comp == "=")
				comp = "equal";
			else if (comp == ">")
				comp = "greater";
			else
			{
				string e = "���� B0026:'" + comp + "'������Ч���߼��������";
				throw e;
			}
			tm->deleteData(comp, key, tableName);
			return true;
		}
		else 
		{
			string e = "���� B0027:'" + a[3] + "'��������SQL�﷨����";
			throw e;
		}
	}
	else
	{
		string e = "���� B0028:'" + a[2] + "'��������SQL�﷨����";
		throw e;
	}
	return false;
}
// insert into [tablename] values ( A B C ) ;
bool UI::insert(string a[], int n, TableManager*& tm) throw (const string)
{
	isSelectDB(tm);

	if (a[1] == "into" && a[3] == "values")
	{
		string tableName = a[2]; 
		string str[10];//
		int i = 4;
		int j = 0;
		while(a[i] != "")
		{
			str[j] = a[i];
			j++;
			i++;
			//if (a[i] == "")
			//{
			//	string e = "���� B0029:'" + a[i-1] + "'��������SQL�﷨����";
			//	throw e;
			//}
		}
		tm->insertData(str, tableName);
		return true;
	}
	else
	{
		string e = "���� B0030:SQL�﷨���󣬲���ʧ�ܣ�";
		throw e;
	}
}
// show tables ;
// show databases;
bool UI::show(string a[], int n, TableManager*& tm, DataBase& db)
{
	if (a[1] == "databases" && a[2] == "")
	{
		TableManager* temp;
		db.m_db.setStart();
		int length = db.m_db.rightLength();
		if (length > 0)
		{
			cout << "DataBases:" << endl;
			for (int i = 0; i < length; i++)
			{
				db.m_db.getValue(temp);
				cout << temp->getDataBaseName() << endl;
				db.m_db.next();
			}
			cout << length << "�����ݿ���ã�" << endl;
		}
		else
		{
			cout << "empty   " << "û�����ݿ���ã�"<< endl;
		}
		return true;
	}

	if (a[1] == "tables" && a[2] == "")
	{
		isSelectDB(tm); // �ж�tm

		tm->showTables();
		cout << "�����ɹ���" << endl;
		return true;
	}
	else
	{
		string e = "���� B0031:'" + a[1] + "'��������SQL�﷨����";
		throw e;
	}
}
// drop [tablename] ;
// drop database [dbName];
bool UI::drop(string a[], int n, TableManager*& tm, DataBase& db)
{
	

	MyTable* temp;
	string tableName = a[1];
	if (a[1] == "database" && a[2] != "" && a[3] == "")
	{
		string dbName = a[2];
		if (tm != NULL && tm->getDataBaseName() == dbName)
			tm = NULL;
		db.DropDataBase(dbName);
		cout << "ɾ���ɹ���" << endl;
		return true;
	}
	else if (a[1] != "" && a[2] =="")
	{
		isSelectDB(tm);
		tm->getTable(temp, tableName);
		tm->deleteTable(tableName);
		cout << "�����ɹ���" << endl;
		return true;
	}
	else 
	{
		string e = "���� B0032:'" + a[1] + "'��������SQL�﷨����";
		throw e;
	}
}
// alter [tablename] add [columnname] [datatype] ;
// alter [tablename] drop [columnname] ;
// alter [tablename] add primary key [columnname] ;
// alter [tablename] add foreign key [columnname] reference [ftablename] [fcolumnname] ;
bool UI::alter(string a[], int n, TableManager*& tm)
{
	isSelectDB(tm);

	string tableName = a[1];
	string columnName = a[3];
	if (a[2] == "add")
	{
		string columnType = a[4];
		if (a[3] == "primary" && a[4] == "key")
		{
			columnName = a[5];
			tm->setPrimary(columnName, tableName);
			return true;
		}
		else if (a[3] == "foreign" && a[4] == "key" && a[6] == "reference")
		{
			columnName = a[5];
			string fTableName = a[7];
			string fColumnName = a[8];
			tm->setForeign(columnName,fColumnName,fTableName,tableName);
			return true;
		}
		else if (a[5] == "")
		{
			tm->alterTable(columnName, columnType, tableName);
			return true;
		}
		else
		{
			string e = "���� B0033:'" + a[3] + "'��������SQL�﷨����";
			throw e;
		}
	}
	else if (a[2] == "drop" && a[4] == "")
	{
		tm->dropTableColumn(columnName, tableName);
		return true;
	}
	else 
	{
		string e = "���� B0034:'" + a[2] + "'��������SQL�﷨����";
		throw e;
	}
}
// create database [DBName];
// create index [tablename] [columnname] ;
// create table [tablename] ;
bool UI::create(string a[], int n, TableManager*& tm, DataBase& db)
{
	if (a[1] == "database" && a[3] == "")
	{
		string dbName = a[2];
		if (db.IsExist(dbName))
		{
			string e = "���� B0037:���ݿ�'" + a[2] + "'�Ѿ����ڣ�";
			throw e;
		}
		TableManager* temp = new TableManager(dbName);
		db.CreateDataBase(temp);
		cout << "�����ɹ���" << endl;
		return true;
	}

	else if (a[1] == "table" && a[3] == "")
	{
		isSelectDB(tm);

		string tableName = a[2];
		tm->createTable(tableName);
		return true;
	}
	else if (a[1] == "index" && a[4] == "")
	{
		isSelectDB(tm);

		string tableName = a[2];
		string columnName = a[3];

		tm->setIndex(columnName, tableName);
		return true;
	}
	else
	{
		string e = "���� B0035:'" + a[1] + "'��������SQL�﷨����";
		throw e;
	}
}

// update [tablename] set [columnname] = [value] where [primaryKey] = [index] ;
bool UI::update(string a[], int n, TableManager*& tm)
{
	isSelectDB(tm);

	string tableName = a[1];
	string columnName = a[3];
	string value = a[5];
	int index = MyString::StringToInt(a[9]);
	if(a[2] == "set")
	{
		if (a[6] == "where")
		{
			tm->updataData(index, columnName,value,tableName);
			return true;
		}
		else if (a[6] == "")
		{
			// TODO:��������������ȫ������
			return true;
		}
		else
		{
			string e = "���� B0036:'" + a[6] + "'��������SQL�﷨����";
			throw e;
		}
	}
	else
	{
		string e = "���� B0037:'" + a[2] + "'��������SQL�﷨����";
		throw e;
	}
}
// describe [tablename] ;
// describe [tablename] table relation ;
bool UI::describe(string a[], int n, TableManager*& tm)
{
	isSelectDB(tm);

	if (a[2] == "table" && a[3] == "relation")
	{
		string tableName = a[1];
		tm->getTableRelation(tableName);
		return true;
	}
	else if (a[2] == "")
	{
		string tableName = a[1];
		tm->describe(tableName);
		return true;
	}
	else
	{
		string e = "���� B0038:'" + a[2] + "'��������SQL�﷨����";
		throw e;
	}
}
// save ;
// save [tablename];
bool UI::save(string a[], int n, TableManager*& tm)
{
	if (a[1] == "")
	{
		tm->SaveTableLabels();
		return true;
	}
	else if (a[2] == "")
	{
		string tableName = a[1];
		tm->saveData(tableName);
		return true;
	}
	else
	{
		string e = "���� B0039:'" + a[2] + "'��������SQL�﷨����";
		throw e;
	}
}
#endif