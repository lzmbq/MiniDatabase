/********************************************************************
	created:	2008/06/15
	created:	15:6:2008   23:02
	modified:	
	filename: 	TableManager
	file ext:	cpp
	author:		
	
	purpose:	完成对表的增删查改操作，以及数据的增删查改
*********************************************************************/
#include "TableManager.h"

bool TableManager::setDataBaseName(string name)
{
	this->m_sDataBaseName = name;
	return true;
}
string TableManager::getDataBaseName() const
{
	return this->m_sDataBaseName;
}

bool TableManager::createTable(MyTable& t)
{
//	m_DataBase = t;
//	创建路径
	/*string path = "data\\";
	string cmd = "mkdir " + t.GetTableName();
	system(cmd.c_str());*/
	this->m_DataBase->insert(&t);
	return true;
}
bool TableManager::describe(const string & tableName)
{
	MyTable* temp;
	getTable(temp,tableName);
	temp->Describe("tableTpye");
	return true;
}

// 查看表间关系
bool TableManager::getTableRelation(const string & tableName)
{
	MyTable* temp;
	getTable(temp,tableName);
	temp->Describe("relation");
	return true;
}

bool TableManager::saveData(const string & tableName)
{
	MyTable *temp;
	getTable(temp,tableName);
	temp->SaveData();
	return true;
}
bool TableManager::createTable(const string & tableName)
{
	MyTable* temp;
	int i = 0;
	for(; i < m_DataBase->length(); i++)
	{
		m_DataBase->setPos(i);
		m_DataBase->getValue(temp);
		if (temp->GetTableName() == tableName)
		{
			string e = "错误 C0031:'" + tableName + "'表已经存在！";
			throw e;
		}
		m_DataBase->next();
	}
	MyTable* t = new MyTable(tableName, m_sDataBaseName);
	this->m_DataBase->insert(t);
	//	创建路径
	//string path = "data\\";
	//string cmd = "mkdir " + path + t->GetTableName();
	//system(cmd.c_str());
	cout << "创建表成功！" << endl;
	this->SaveTableLabels();
	return true;
}

bool TableManager::getTable(MyTable*& temp, const string & tableName)
{
	int i = 0;
	for(; i < m_DataBase->length(); i++)
	{
		m_DataBase->setPos(i);
		m_DataBase->getValue(temp);
		if (temp->GetTableName() == tableName)
		{
			break;
		}
		m_DataBase->next();
	}
	if(i >= m_DataBase->length())
	{
		string e = "错误 C0030:表'" + tableName + "'不存在！";
		throw e;
	}
	return true;
}


bool TableManager::deleteTable(const string &tableName)
{
	MyTable* temp;
	int i = 0;
	getTable(temp,tableName);
	for(; i < m_DataBase->length(); i++)
	{
		m_DataBase->setPos(i);
		m_DataBase->getValue(temp);
		if (temp->GetTableName() == tableName)
		{
			if (temp->GetParentName() != "NULL")
			{
				string e = "错误 C0032:表'" + tableName + "'与'" + temp->GetParentName() + "'存在关联，不能进行删除操作！";
				throw e;
			}
			m_DataBase->remove(temp);
//			cout << path + tableName + ".txt"; 测试
			remove((path + tableName + ".txt").c_str());
			return true;
		}
		m_DataBase->next();
	}
	return false;
}
bool TableManager::alterTable(const string& columnName, const string& columnType, const string& tableName)
{
	MyTable* temp;
	int i = 0;
	getTable(temp,tableName);
	for(; i < m_DataBase->length(); i++)
	{
		m_DataBase->setPos(i);
		m_DataBase->getValue(temp);
		if (temp->GetTableName() == tableName)
		{
			temp->AlterTable(columnName, columnType);
			return true;
		}
		m_DataBase->next();
	}
	//cout << "此数据库中不包含" << tableName << "表！不能完成修改列操作！" << "\007" << endl;
	return false;
}
// 补充设置主键
bool TableManager::setPrimary(const string& columnName, const string & tableName)
{
	MyTable *temp;
	getTable(temp,tableName);
	//{
	//	cout << "不能完成设置主键的操作！表不存在！" << "\007" << endl;
	//	return false;
	//}
	temp->SetPrimary(columnName);
	return true;
}
// 补充设置外键
bool TableManager::setForeign(const string& columnName, const string& fColumnName, const string & fTableName, const string & tableName)
{
	MyTable *temp1;
	MyTable* temp2;
	getTable(temp1,tableName);
	//{
	//	cout << "不能完成设置外键的操作！父表不存在！" << "\007" << endl;
	//	return false;
	//}
	getTable(temp2,fTableName);
	//{
	//	cout << "不能完成设置外键的操作！子表不存在！" << "\007" << endl;
	//	return false;
	//}

	if (temp2->GetColumn(fColumnName).getColName() == "")
		return false;
	
	if(temp1->SetForeign(columnName, fColumnName, fTableName))
	{
		string  parentName = tableName + '/' +columnName + '/';
		temp2->SetParentName(parentName);
		return true;
	}
	return true;
}
bool TableManager::dropTableColumn(const string& columnName, const string& tableName)
{
	MyTable *temp;
	getTable(temp,tableName);
	//{
	//	cout << "不能完成删除列的操作！表不存在！" << "\007" << endl;
	//	return false;
	//}
	temp->DropTableColumn(columnName);
	return true;
}
bool TableManager::insertData(string data[], const string & tableName)
{
	MyTable *temp;
	getTable(temp,tableName);
	int i = 0;
	while(data[i] != "")
	{
		i++;
	}
	
	temp->Insert(data, i);

	return true;
}
// 通过主键索引升序查找数据
bool TableManager::selectData(LList<string>& columnList, const string& comp,const int & sql,const string & tableName)
{
	MyTable *temp;
	getTable(temp,tableName);
	//{
	//	cout << "不能完成此检索操作！表不存在！" << "\007" << endl;
	//	return false;
	//}
	
	temp->Select(columnList, comp ,sql);
	return true;
}
// 通过主键索引降序查找数据
bool TableManager::selectDataByDesc(LList<string>& columnList, const string& comp, const int & sql,const string & tableName)
{
	MyTable *temp;
	getTable(temp,tableName);
	//{
	//	cout << "不能完成此检索操作！表不存在！" << "\007" << endl;
	//	return false;
	//}
	
	temp->SelectByDesc(columnList, comp ,sql);
	return true;

}
// 查找表中所有数据
bool TableManager::selectData(LList<string>& columnList,const string & tableName)
{
	MyTable *temp;
	getTable(temp,tableName);
	//{
	//	cout << "不能完成此检索操作！表不存在！" << "\007" << endl;
	//	return false;
	//}
	temp->Select(columnList);
	return true;
}

// 查找表中排序后的所有数据
// 通过非主键索引查找
bool TableManager::selectData(LList<string>& columnList,const string& column, const string & tableName)
{
	MyTable *temp;
	getTable(temp,tableName);
	//{
	//	cout << "不能完成此检索操作！表不存在！" << "\007" << endl;
	//	return false;
	//}
	temp->Select(columnList, column);
	return true;
}
 
bool TableManager::deleteData(const string& comp, const int & sql,const string & tableName)
{
	MyTable *temp;
	getTable(temp,tableName);
	//{
	//	cout << "不能完成此删除操作！表不存在！" << "\007" << endl;
	//	return false;
	//}
	
	temp->Delete(comp ,sql);
	return true;
}

bool TableManager::updataData(int index, const string& columnName, const string& value, const string & tableName)
{
	MyTable *temp;
	getTable(temp,tableName);
	//{
	//	cout << "不能完成此修改操作！表不存在！" << "\007" << endl;
	//	return false;
	//}
	
	temp->Updata(index,columnName,value);
	return true;
}

bool TableManager::setIndex(const string & columnName, const string & tableName)
{
	MyTable *temp;
	getTable(temp,tableName);
	//	cout << "不能完成设置索引操作！表不存在！" << "\007" << endl;
	//	return false;
	//}
	if (temp->GetColumn(columnName).getFlog() == 1)
	{
		if(temp->SetIndex(columnName))
		{
			cout << "设置索引成功！" << endl;
			this->saveData(tableName);
			return true;
		}
	}
	else
	{
		if(temp->SetStrIndex(columnName))
		{
			cout << "设置索引成功！" << endl;
			this->saveData(tableName);
			return true;
		}
	}
	return false;
}

bool TableManager::LoadTableLabels()
{
	string tableName;
	int length;
	m_file->Open('i');
	length = m_file->ReadInt();
	MyTable* t[20];// 表的个数
	for (int i = 0; i < length; i++)
	{
		t[i] = new MyTable(m_file->ReadStr(), m_sDataBaseName);
		t[i]->LoadData();
		this->m_DataBase->append(t[i]);
	}
	m_file->Close('i');
	return true;
}
bool TableManager::SaveTableLabels()
{
	m_file->Open('o');
	MyTable* temp;
	m_file->WriteInt(m_DataBase->length());
	for(int i = 0; i < m_DataBase->length(); i++)
	{
		m_DataBase->setPos(i);
		m_DataBase->getValue(temp);
		m_file->WriteStr(temp->GetTableName());
		temp->SaveData();
		m_DataBase->next();
	}
	m_file->Close('o');
//	cout << "所有表的信息保存成功！" << endl;
	return true;
}
bool TableManager::Remove()
{
	MyTable* temp;
	string filePath;
	m_DataBase->setStart();
	int length = m_DataBase->rightLength();
	for (int i = 0; i < length; i++)
	{
		m_DataBase->getValue(temp);
		filePath = this->path + temp->GetTableName() + ".txt";
		remove(filePath.c_str());
		delete temp;
		m_DataBase->next();
	}
	return true;
}
bool TableManager::showTables()
{
	MyTable* temp;
	if (m_DataBase->length() == 0)
	{
		string e = "错误 C0033:当前数据库中没有表！";
		throw e;
	}
	for(int i = 0; i < m_DataBase->length(); i++)
	{
		m_DataBase->setPos(i);
		m_DataBase->getValue(temp);
		cout << temp->GetTableName() << endl;
		m_DataBase->next();
	}
	return true;
}	
