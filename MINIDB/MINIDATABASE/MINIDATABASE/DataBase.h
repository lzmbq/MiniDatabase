/********************************************************************
	created:	2008/08/01
	created:	
	modified:	
	filename: 	
	file ext:	h
	author:		
	
	purpose:	管理数据库
*********************************************************************/
#ifndef DATABASE_H_
#define DATABASE_H_
#include "AList.h"
#include "TableManager.h"
class DataBase
{
private:
	//string m_DBManagerName;
	int m_iDBCount;
	CFileRW* m_file;
	
	bool RemoveDBManager();
	bool LoadDB();
	bool SaveDB();
public:
	DataBase();
	~DataBase();
	AList<TableManager*> m_db;
	bool CreateDataBase(TableManager* db);
	bool DropDataBase(const string& DBName) throw (const string);;
	bool IsExist(const string& DBName);
};
DataBase::DataBase()
{
//	m_DBManagerName = dbName;
	m_file = new CFileRW("data\\DBInfo.txt");
	LoadDB();
}

DataBase::~DataBase()
{
	SaveDB();
	RemoveDBManager();
	delete m_file;
}
bool DataBase::RemoveDBManager()
{
	TableManager* temp;
	m_db.setStart();
	for (int i = 0; i < m_db.rightLength(); i++)
	{
		m_db.remove(temp);
		delete temp;
		m_db.next();
	}
	return true;
}

bool DataBase::LoadDB()
{
	TableManager* temp;
	string DBName;
	m_file->Open('i');
	m_iDBCount = m_file->ReadInt();
	for (int i = 0; i < m_iDBCount; i++)
	{
		DBName = m_file->ReadStr();
		temp = new TableManager(DBName);
		m_db.insert(temp);
	}
	m_file->Close('i');
	return true;
}

bool DataBase::SaveDB()
{
	TableManager* temp;
	m_file->Open('o');
	m_db.setStart();
	m_iDBCount = m_db.rightLength();
	m_file->WriteInt(m_iDBCount);
	for (int i = 0; i < m_iDBCount; i++)
	{
		m_db.getValue(temp);
		m_file->WriteStr(temp->getDataBaseName());
		m_db.next();
	}
	m_file->Close('o');
	return true;
}
bool DataBase::CreateDataBase(TableManager* db)
{
	string path = "data\\" + db->getDataBaseName() + "\\";
	m_db.setStart();
	//cout << m_db.rightLength();
	m_db.setPos(m_db.rightLength());
	m_db.insert(db);
	system(("mkdir " + path).c_str());

	// 保存
	SaveDB();
	return true;
}

bool DataBase::DropDataBase(const string& DBName)
{
	TableManager* temp;
	bool isDrop=false;
	m_db.setStart();
	int length = m_db.rightLength();
	for (int i = 0; i < length; i++)
	{
		m_db.getValue(temp);
		if (DBName == temp->getDataBaseName())
		{
			m_db.remove(temp);
			delete temp;
			isDrop = true;
			break;
		}
		m_db.next();
	}
	if (isDrop != true)
	{
		string e = "错误 F0001:数据库'" + DBName + "'不存在！";
		throw e;
	}
	string filePath = "data\\" + DBName + "\\" + DBName + ".txt";
	remove(filePath.c_str());
	string path = "data\\" + DBName + "\\";
	system(("rmdir " + path).c_str());

	this->SaveDB();
	return true;
}

bool DataBase::IsExist(const string& DBName)
{
	TableManager* temp;
	m_db.setStart();
	int length = m_db.rightLength();
	for (int i = 0; i < length; i++)
	{
		m_db.getValue(temp);
		if (DBName == temp->getDataBaseName())
			return true;
		m_db.next();
	}
	return false;
}
#endif