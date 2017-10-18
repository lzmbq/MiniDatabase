/********************************************************************
	created:	2008/06/15
	created:	15:6:2008   23:02
	modified:	
	filename: 	MyTable
	file ext:	cpp
	author:		
	
	purpose:	对数据实现增删查改操作
*********************************************************************/
#include "MyTable.h"




MyTable::MyTable(TableHead& t, const string& tableName)
{
//	m_pStrTableName = "";
//	m_iColumnCount = 0; 
	//	cout <<m_iColumnCount;
//	m_iAllColumnSize = 0;

	this->m_TableHead = &t;
	m_IndexColumn = 0;
	m_Index = NULL;
	this->SetTableName(tableName);
	m_file = new CFileRW((tableName+".txt").c_str());
	m_bLoaded = false;
//	this->m_pListColumn.insert(c);
}


/*
bool MyTable::DeleteColumn(Column& c, string columnName)
{
	Column temp;
	for (int i = 0; i < m_pListColumn.leftLength(); i++)
	{
		m_pListColumn.getValue(temp);
		if (columnName == temp.getColName())
			break;
	}
	this->m_pListColumn.setPos(i);
	this->m_pListColumn.remove(c);
	m_iColumnCount--;
	return true;
}


Column MyTable::GetColmn(int i)
{
	Column temp;
	this->m_pListColumn.setPos(i+1);
	this->m_pListColumn.getValue(temp);
	return temp;
}

int MyTable::GetColumnCount() const
{
	return this->m_iColumnCount;
}*/

int MyTable::IsTableColumn(const string& columnName) // 返回tablehead的位置，不在返回-1
{
	for (int i = 0; i < m_TableHead->GetColumnCount(); i++)
		if (m_TableHead->GetColmn(i).getColName() == columnName)
			return i;
	return -1;
}

string MyTable::GetTableName() const
{
	return this->m_pStrTableName;
}

bool MyTable::Describe(const string& operType)
{
	Column c;
	string columnName;
	int dataSize;
	int dataType;
	int dataFlog;
	string type;
	string flog;
	if (operType == "relation")
	{
	
		if (m_TableHead ==NULL)
		{
			cout << "您还没有向表中加入列！" << "\007" << endl;
			return false;
		}
		string parentTableName;
		string parentColumnName;
		if (m_pParent != "NULL")
		{
			MyString::Analyse(m_pParent, parentTableName, 0);
			MyString::Analyse(m_pParent, parentColumnName, 1);
		}
		bool isExistForeign = false;
		bool isExistParent = false;
		for (int i = 0; i < m_TableHead->GetColumnCount(); i++)
		{
			c = m_TableHead->GetColmn(i);
			columnName = c.getColName();
			dataFlog = c.getFlog();
			cout << columnName;
			if (dataFlog == 2)
			{
				isExistForeign = true;
				cout << "------------>" << c.getStrForTableName() << "." << c.getStrForColName();
			}
			if (dataFlog == 1 && m_pParent != "NULL")
			{
				isExistParent = true;
				cout << "<------------" << parentTableName << "." << parentColumnName;
			}
			cout << endl;
		}
		if (isExistForeign == false && isExistParent == false)
			cout << "不存在与此表关联的表！" << "\007" << endl;
		else
			cout << "操作成功！" << endl;
		return true;
	}
	else if (operType == "tableTpye")
	{
		// 打印描述表的表头
		string temp = "Field";
		cout << left << setw(15) <<temp;

		temp = "Type";
		cout << left << setw(15) <<temp;

		temp = "Key";
		cout << left << setw(15) <<temp;
		
		temp = "IsNull";
		cout << left << setw(15) <<temp;

		cout << endl;
		if (m_TableHead ==NULL)
		{
			cout << "您还没有向表中加入列！" << "\007" << endl;
			return false;
		}
		for (int i = 0; i < m_TableHead->GetColumnCount(); i++)
		{
			c = m_TableHead->GetColmn(i);
			columnName = c.getColName();
			dataSize = c.getDataSize();
			dataType = c.getDataType();
			dataFlog = c.getFlog();

			cout << left << setw(15) <<columnName;

			// enum E_DATA_TYPE{MY_CHAR,MY_SHORT,MY_INT,MY_LONG,MY_FLOAT,MY_DOUBLE,MY_VARCHAR};
			if (dataType == 0)
				type = "char";
			else if (dataType == 1)
				type = "short";
			else if (dataType == 2)
				type = "int";
			else if (dataType == 3)
				type = "long";
			else if (dataType == 4)
				type = "float";
			else if (dataType == 5)
				type = "double";
			else if (dataType == 6)
			{
				type = "varchar";
				type = type+ '(' + MyString::IntToString(dataSize) + ')';
			}
			cout << left << setw(15) <<type;

			if (dataFlog == 1)
				flog = "primary,index";
			else if (dataFlog == 3)
				flog = "index";
			else if (dataFlog == 2)
				flog = "foreign";
			else
				flog = "";
			cout << left << setw(15) <<flog;

			cout << endl;
		}
		cout << "操作成功！" << endl;
		return true;
	}
	return false;
}
bool MyTable::Insert(string data[], const int n)
{
	if (n != m_TableHead->GetColumnCount())
	{
		string e = "错误 E0002:插入项数与表中列数不符！";
		throw e;
	}
	// 检查类型是否匹配
	// enum E_DATA_TYPE{MY_CHAR,MY_SHORT,MY_INT,MY_LONG,MY_FLOAT,MY_DOUBLE,MY_VARCHAR,MY_MAX_TYPE};
	for (int i = 0; i < n; i++)
	{
		if (m_TableHead->GetColmn(i).getDataType() == 0)
		{
			MyString::IsChar(data[i]);
		}
		else if (m_TableHead->GetColmn(i).getDataType() == 1)
		{
			MyString::IsShort(data[i]);
		}
		else if (m_TableHead->GetColmn(i).getDataType() == 2)
		{
			MyString::IsInt(data[i]);
		}
		else if (m_TableHead->GetColmn(i).getDataType() == 3)
		{
			MyString::IsLong(data[i]);
		}
		else if (m_TableHead->GetColmn(i).getDataType() == 4)
		{
			//MyString::IsFloat(data[i]);
		}
		else if (m_TableHead->GetColmn(i).getDataType() == 5)
		{
			//MyString::IsDouble(data[i]);
		}
		else if (m_TableHead->GetColmn(i).getDataType() == 6)
		{
			if (data[i][0] != '\'' && data[i][data[i].length()] != '\'')
			{
				string e = "错误 E0001:'" + data[i] + "'应为varchar类型，插入时需加入''！";
				throw e;
			}
			string temp = data[i].substr(1,(data[i].length()-2));
			//data[i] = temp;
			//cout << temp; 测试'ee'截为ee是否成功
			data[i] = temp;
			MyString::IsVarChar(data[i], m_TableHead->GetColmn(i).getDataSize());
		}
	}

	string record = MyString::Create(data,this->GetColumnLength());
	int pos = -1;
	string str;
	int index, temp;
	for (int i = 0; i < m_TableHead->GetColumnCount(); i++)
	{
		if( m_TableHead->GetColmn(i).getFlog() == 1 )
		{
			pos = i;
			break;
		}
	}
	if (pos != -1)
	{
		MyString::Analyse(record, str, pos);
		index = MyString::StringToInt(str);
		if (m_Index->AVLFind(index, temp))
		{
			cout << "插入记录，主键不能重复！" << "\007" << endl;
			return false;
		}
	}
	//m_TableBody.Allocate(record);
	m_Index->AVLInsert(index,m_TableBody.Allocate(record));
	cout << "1行受影响！" << endl;

	this->SaveData();
	return true;
}


void MyTable::SetTableName(const string & name)
{
	this->m_pStrTableName = name;
}

int MyTable::GetColumnLength()
{
	return m_TableHead->GetColumnCount();
}

bool MyTable::Select(LList<string>& columnList)
{
	LList<int> columnPos;
	int addr;
	string substr;
	// 打印表头
	if (!PrintTableHead(columnList, columnPos))
			return false;
	for (int m = 1; m <= m_TableBody.GetLength(); m++)
	{
		addr = m_TableBody.GetAvailableData(m);
		columnPos.setStart();
		int length = columnPos.rightLength();
		int pos;
		for (int i = 0; i < length; i++)
		{
			columnPos.setPos(i);
			columnPos.getValue(pos);
			MyString::Analyse(m_TableBody.GetValue(addr),substr,pos);
			cout << left << setw(15) <<substr;
			columnPos.next();
		}
		cout << endl;
	}
	cout << m_TableBody.GetLength() << "行受影响！" << endl;
	return true;
}
bool MyTable::Select(LList<string>& columnList, const string& comp,int sql)
{
	LList<int> columnPos;
	if (comp == "equal")
	{
		int addr;
		string substr;
		if (!this->m_Index->AVLFind(sql,addr))
		{
			cout << "您查找的数据不存在！" << "\007" << endl;
			return false;
		}
		// 打印表头
		if (!PrintTableHead(columnList, columnPos))
			return false;
		columnPos.setStart();
		int length = columnPos.rightLength();
		int pos;
		for (int i = 0; i < length; i++)
		{
			columnPos.setPos(i);
			columnPos.getValue(pos);
			MyString::Analyse(m_TableBody.GetValue(addr),substr,pos);
			cout << left << setw(15) <<substr;
			columnPos.next();
		}
		cout << endl;
		cout << "1行受影响！";
		cout << endl;
		
		return true;
	}
	else
	{

		LList<int> * set = new LList<int>();
		int addr;
		string substr;
		int rows;
		if (!m_Index->AVLFindSet(comp, sql,set))
		{
			cout << "没有您要查找的数据！" << "\007" << endl;
			return false;
		}
		else
		{
			// 打印表头
			if (!PrintTableHead(columnList, columnPos))
				return false;
			set->setStart();
			rows = set->rightLength();
			do
			{
				set->getValue(addr);
				columnPos.setStart();
				int length = columnPos.rightLength();
				int pos;
				for (int i = 0; i < length; i++)
				{
					columnPos.setPos(i);
					columnPos.getValue(pos);
					MyString::Analyse(m_TableBody.GetValue(addr),substr,pos);
					cout << left << setw(15) <<substr;
					columnPos.next();
				}
				cout << endl;
				set->next();
			}while (set->rightLength());
			cout << rows << "行受影响！" << endl;
			return true;	
		}
		
	}
	return false;
	
}
bool MyTable::SelectByDesc(LList<string>& columnList, const string& comp, int sql)
{
	LList<int> columnPos;
	if (comp == "equal")
	{
		int addr;
		string substr;
		if (!this->m_Index->AVLFind(sql,addr))
		{
			cout << "您查找的数据不存在！" << "\007" << endl;
			return false;
		}
		// 打印表头
		if (!PrintTableHead(columnList, columnPos))
			return false;
		columnPos.setStart();
		int length = columnPos.rightLength();
		int pos;
		for (int i = 0; i < length; i++)
		{
			columnPos.setPos(i);
			columnPos.getValue(pos);
			MyString::Analyse(m_TableBody.GetValue(addr),substr,pos);
			cout << left << setw(15) <<substr;
			columnPos.next();
		}
		cout << endl;
		cout << "1行受影响！";
		cout << endl;
		
		return true;
	}
	else
	{

		LList<int> * set = new LList<int>();
		int addr;
		string substr;
		int rows;
		if (!m_Index->AVLFindSet(comp, sql,set))
		{
			cout << "没有您要查找的数据！" << "\007" << endl;
			return false;
		}
		else
		{
			// 打印表头
			if (!PrintTableHead(columnList, columnPos))
				return false;
			rows = set->rightLength();
			for (int m = 1; m < rows; m++)
			{
				set->next();
			}
			for(int n = 0; n < rows; n++)
			{
				set->getValue(addr);
				columnPos.setStart();
				int length = columnPos.rightLength();
				int pos;
				for (int i = 0; i < length; i++)
				{
					columnPos.setPos(i);
					columnPos.getValue(pos);
					MyString::Analyse(m_TableBody.GetValue(addr),substr,pos);
					cout << left << setw(15) <<substr;
					columnPos.next();
				}
				cout << endl;
				set->prev();
			}
			cout << rows << "行受影响！" << endl;
			return true;	
		}
		
	}
	return false;
}
//非主键hash索引
bool MyTable::Select(LList<string>& columnList, const string& columnName)
{
	LList<int> columnPos;
	int set[30];
	int count = m_Index->HashGetAddr(set, columnName);
	string substr;
	// 打印表头
	if (!PrintTableHead(columnList, columnPos))
			return false;
	for (int j = 0; j < count; j++)
	{
		columnPos.setStart();
		int length = columnPos.rightLength();
		int pos;
		for (int i = 0; i < length; i++)
		{
			columnPos.setPos(i);
			columnPos.getValue(pos);
			MyString::Analyse(m_TableBody.GetValue(set[j]),substr,pos);
			cout << left << setw(15) <<substr;
			columnPos.next();
		}
		cout << endl;
	}
	cout << count << "行受影响！" << endl;
	return true;
}
//E_DATA_TYPE{MY_CHAR,MY_SHORT,MY_INT,MY_LONG,MY_FLOAT,MY_DOUBLE,MY_PCHAR,MY_MAX_TYPE}
bool MyTable::AlterTable(const string& columnName, const string& columnType)
{
	Column c;
	string record;
	if (m_TableHead != NULL )
	{
		for (int j = 0; j < m_TableHead->GetColumnCount(); j++)
		{
			if (m_TableHead->GetColmn(j).getColName() == columnName)
			{
				cout << "您要插入的列名在表中已存在！" << "\007" << endl;
				return false;
			}
		}
	}
	else
		m_TableHead = new TableHead();
	c.setColName(columnName);
	if (columnType == "char")
	{
		c.setDataType(E_DATA_TYPE(0));
		c.setDataSize(1);
		c.setFlog(4);
		c.setStrForColName("NULL");
		c.setStrForTableName("NULL");
		m_TableHead->AddColumn(c);
		for (int i = 0; i < m_TableBody.GetLength(); i++)
		{
			record = m_TableBody.GetValue(m_TableBody.GetAvailableData(i+1));
			record = record + "NULL/";
			m_TableBody.Updata(record, m_TableBody.GetAvailableData(i+1));
		}
		cout << "修改成功！" << endl;

		this->SaveData();
		return true;
	}
	else if (columnType == "short")
	{
		c.setDataType(E_DATA_TYPE(1));
		c.setDataSize(4);
		c.setFlog(4);
		c.setStrForColName("NULL");
		c.setStrForTableName("NULL");
		m_TableHead->AddColumn(c);
		for (int i = 0; i < m_TableBody.GetLength(); i++)
		{
			record = m_TableBody.GetValue(m_TableBody.GetAvailableData(i+1));
			record = record + "NULL/";
			m_TableBody.Updata(record, m_TableBody.GetAvailableData(i+1));
		}
		cout << "修改成功！" << endl;

		this->SaveData();
		return true;
	}
	else if (columnType == "int")
	{
		c.setDataType(E_DATA_TYPE(2));
		c.setDataSize(4);
		c.setFlog(4);
		c.setStrForColName("NULL");
		c.setStrForTableName("NULL");
		m_TableHead->AddColumn(c);
		for (int i = 0; i < m_TableBody.GetLength(); i++)
		{
			record = m_TableBody.GetValue(m_TableBody.GetAvailableData(i+1));
			record = record + "NULL/";
			m_TableBody.Updata(record, m_TableBody.GetAvailableData(i+1));
		}
		cout << "修改成功！" << endl;

		this->SaveData();
		return true;
	}
	else if (columnType == "long")
	{
		c.setDataType(E_DATA_TYPE(3));
		c.setDataSize(8);
		c.setFlog(4);
		c.setStrForColName("NULL");
		c.setStrForTableName("NULL");
		m_TableHead->AddColumn(c);
		for (int i = 0; i < m_TableBody.GetLength(); i++)
		{
			record = m_TableBody.GetValue(m_TableBody.GetAvailableData(i+1));
			record = record + "NULL/";
			m_TableBody.Updata(record, m_TableBody.GetAvailableData(i+1));
		}
		cout << "修改成功！" << endl;

		this->SaveData();
		return true;
	}
	else if (columnType == "float")
	{
		c.setDataType(E_DATA_TYPE(4));
		c.setDataSize(8);
		c.setFlog(4);
		c.setStrForColName("NULL");
		c.setStrForTableName("NULL");
		m_TableHead->AddColumn(c);
		for (int i = 0; i < m_TableBody.GetLength(); i++)
		{
			record = m_TableBody.GetValue(m_TableBody.GetAvailableData(i+1));
			record = record + "NULL/";
			m_TableBody.Updata(record, m_TableBody.GetAvailableData(i+1));
		}
		cout << "修改成功！" << endl;

		this->SaveData();
		return true;
	}
	else if (columnType == "double")
	{
		c.setDataType(E_DATA_TYPE(5));
		c.setDataSize(16);
		c.setFlog(4);
		c.setStrForColName("NULL");
		c.setStrForTableName("NULL");
		m_TableHead->AddColumn(c);
		for (int i = 0; i < m_TableBody.GetLength(); i++)
		{
			record = m_TableBody.GetValue(m_TableBody.GetAvailableData(i+1));
			record = record + "NULL/";
			m_TableBody.Updata(record, m_TableBody.GetAvailableData(i+1));
		}
		cout << "修改成功！" << endl;

		this->SaveData();

		return true;
	}
	else if (columnType == "varchar")
	{
		c.setDataType(E_DATA_TYPE(6));
		c.setDataSize(20);
		c.setFlog(4);
		c.setStrForColName("NULL");
		c.setStrForTableName("NULL");
		m_TableHead->AddColumn(c);
		for (int i = 0; i < m_TableBody.GetLength(); i++)
		{
			record = m_TableBody.GetValue(m_TableBody.GetAvailableData(i+1));
			record = record + "NULL/";
			m_TableBody.Updata(record, m_TableBody.GetAvailableData(i+1));
		}
		cout << "修改成功！" << endl;

		this->SaveData();

		return true;
	}
	else
		cout << "本数据库不支持" << columnType << "类型！"<< "\007" << endl;
	return false;
}
bool MyTable::DropTableColumn(const string& columnName)
{
	Column c;
	int i = 0;
	int pos = -1;
	string allupdata = "";
	string updata;
	for (;i < m_TableHead->GetColumnCount(); i++)
	{
		if (m_TableHead->GetColmn(i).getColName() == columnName)
		{
			pos = i;
			break;
		}
	}
	if (i >= m_TableHead->GetColumnCount())
	{
		cout << "您输入的列名不在表头中！" << "\007" << endl;
		return false;
	}
	
	for (int j = 0; j < m_TableBody.GetLength(); j++)
	{
		for (int m = 0; m < m_TableHead->GetColumnCount(); m++)
		{
			MyString::Analyse(m_TableBody.GetValue( m_TableBody.GetAvailableData(j+1)),updata,m);
			if ( pos == m)
			{
				continue;
			}
			allupdata += (updata + '/');
		}
		m_TableBody.Updata(allupdata, m_TableBody.GetAvailableData(j+1));
		allupdata = "";
	}
	m_TableHead->DeleteColumn(c,columnName);
	cout << "删除列成功！" << endl;
	return true;
	
}

// 补充设置主键
bool MyTable::SetPrimary(const string& columnName)
{
	int i = 0;
	for (;i < m_TableHead->GetColumnCount(); i++)
	{
		if (m_TableHead->GetColmn(i).getColName() == columnName)
		{
			Column c = m_TableHead->GetColmn(i);
			m_TableHead->DeleteColumn(c, columnName);
			c.setFlog(1);
			m_TableHead->AddColumn(c);
			this->SetIndex(columnName);
			cout << "设置主键成功！" << endl;

			this->SaveData();
			return true;
		}
	}
	if (i >= m_TableHead->GetColumnCount())
	{
		cout << "您要设置的列不存在！" << "\007" << endl;
	}
	return false;
}
bool MyTable::SetForeign(const string& columnName, const string& fColumnName, const string & fTableName)
{
	int i = 0;
	for (;i < m_TableHead->GetColumnCount(); i++)
	{
		if (m_TableHead->GetColmn(i).getColName() == columnName)
		{
			Column c = m_TableHead->GetColmn(i);
			m_TableHead->DeleteColumn(c, columnName);
			c.setFlog(2);
			c.setStrForColName(fColumnName);
			c.setStrForTableName(fTableName);
			m_TableHead->AddColumn(c);
			cout << "设置外键成功！" << endl;
			return true;
		}
	}
	if (i >= m_TableHead->GetColumnCount())
	{
		cout << "您要设置的列不存在！" << "\007" << endl;
	}
	return false;
}
bool MyTable::SetParentName(const string& parentName)
{
	m_pParent = parentName;
	this->SaveData();
	return true;
}

string MyTable::GetParentName() const
{
	return m_pParent;
}
bool MyTable::Delete(const string& comp, int sql)
{
	int addr;
	BinNode<int> * t;
	LList<int> * set = new LList<int>();
	int rows;
	string allrecord;
	string record;
	if (comp == "equal")
	{
		if (!this->m_Index->AVLFind(sql,addr))
		{
			cout << "您查找的数据不存在！" << "\007" << endl;
			return false;
		}
		this->m_Index->AVLFind(sql,addr);
		allrecord = m_TableBody.GetValue(addr);
		m_TableBody.Deallocate(addr);
		this->m_Index->AVLRemove(sql,t);
		//删除非主键索引
		for (int i = 0; i < m_TableHead->GetColumnCount(); i++)
		{
			if( m_TableHead->GetColmn(i).getFlog() == 3)
			{
				MyString::Analyse(allrecord, record, i);
				m_Index->HashDelete(record, addr);
			}
		}
		cout << "1行受影响！" << endl;
		return true;
	}
	else if (comp == "less")
	{
		if (m_Index->AVLFindSet(comp, sql,set))
		{
			set->setStart();
			rows = set->rightLength();
			do
			{
				set->getValue(addr);
				this->m_Index->AVLFind(sql,addr);
				allrecord = m_TableBody.GetValue(addr);
				m_TableBody.Deallocate(addr);
				this->m_Index->AVLRemove(sql,t);
				for (int i = 0; i < m_TableHead->GetColumnCount(); i++)
				{
					if( m_TableHead->GetColmn(i).getFlog() == 3)
					{
						MyString::Analyse(allrecord, record, i);
						m_Index->HashDelete(record, addr);
					}
				}
				set->next();
			}while (set->rightLength());
			cout << rows << "行受影响！" << endl;
			return true;	
		}
	}
	else if (comp == "greater")
	{
		if (m_Index->AVLFindSet(comp, sql,set))
		{
			set->setStart();
			rows = set->rightLength();
			do
			{
				set->getValue(addr);
				this->m_Index->AVLFind(sql,addr);
				allrecord = m_TableBody.GetValue(addr);
				m_TableBody.Deallocate(addr);
				this->m_Index->AVLRemove(sql,t);
				for (int i = 0; i < m_TableHead->GetColumnCount(); i++)
				{
					if( m_TableHead->GetColmn(i).getFlog() == 3)
					{
						MyString::Analyse(allrecord, record, i);
						m_Index->HashDelete(record, addr);
					}
				}
				set->next();
			}while (set->rightLength());
			cout << rows << "行受影响！" << endl;
			return true;	
		}
	}
	return false;
}

bool MyTable::SetIndex(const string & columnName)
{
	int i = 0;
	string record;
	string allRecord;
	for (;i < m_TableHead->GetColumnCount(); i++)
	{
		if (m_TableHead->GetColmn(i).getColName() == columnName)
		{
			m_IndexColumn = i;
			break;
		}
	}
	if (i >= m_TableHead->GetColumnCount())
	{
		cout << "您输入的列名不在表头中！" << "\007" << endl;
		return false;
	}

	if (m_TableBody.GetLength() != 0)
	{
		for (int i = 0; i < m_TableBody.GetLength(); i++)
		{
			allRecord = m_TableBody.GetValue(i);
			MyString::Analyse(allRecord,record,m_IndexColumn);
			m_Index->AVLInsert(MyString::StringToInt(record), m_TableBody.GetAvailableData(i+1));
		}
	}
	return true;
}

//设置非主键索引
bool MyTable::SetStrIndex(const string & columnName)
{
	int i = 0;
	string record;
	string allRecord;
	for (;i < m_TableHead->GetColumnCount(); i++)
	{
		if (m_TableHead->GetColmn(i).getColName() == columnName)
		{
			m_TableHead->GetColmn(i).setFlog(3);
			m_IndexColumn = i;
			break;
		}
	}
	if (i >= m_TableHead->GetColumnCount())
	{
		cout << "您输入的列名不在表头中！" << "\007" << endl;
		return false;
	}

	if (m_TableBody.GetLength() != 0)
	{
		for (int i = 0; i < m_TableBody.GetLength(); i++)
		{
			allRecord = m_TableBody.GetValue(i);
			MyString::Analyse(allRecord,record,m_IndexColumn);
			m_Index->HashInsert(record, m_TableBody.GetAvailableData(i+1));
		}
	}
	
	return true;
}
//更新数据
bool MyTable::Updata(int index, const string& columnName, const string& value)
{
	int i = 0;
	int addr;
	for (;i < m_TableHead->GetColumnCount(); i++)
	{
		if (m_TableHead->GetColmn(i).getColName() == columnName)
		{
			break;
		}
	}
	if (i >= m_TableHead->GetColumnCount())
	{
		cout << "您输入的列名不在表头中！" << "\007" << endl;
		return false;
	}
	
	string updata;
	string allupdata = "";
	if (!m_Index->AVLFind(index,addr))
	{
		cout << "您要检索的数据不在表中，更新失败！" << "\007" << endl;
		return false;
	}
	for (int j = 0; j < m_TableHead->GetColumnCount(); j++)
	{
		MyString::Analyse(m_TableBody.GetValue(addr),updata,j);
		if ( i == j)
		{
			updata = value;
		}
		allupdata += (updata + '/');
	}
	m_TableBody.Updata(allupdata, addr);
	cout << "表中数据更新成功！" << endl;

	this->SaveData();
	return true;
}
//保存数据到文件中
bool MyTable::SaveData()
{
	m_file->Open('o');
	m_file->WriteStr(m_pParent);
	if (m_TableHead == NULL)
	{
		m_file->WriteInt(0);
	}
	else
	{
		m_file->WriteInt(m_TableHead->GetColumnCount());
		for (int i = 0;i < m_TableHead->GetColumnCount(); i++)
		{
			m_file->WriteStr(m_TableHead->GetColmn(i).getColName());
			m_file->WriteInt(m_TableHead->GetColmn(i).getDataType());
			m_file->WriteInt(m_TableHead->GetColmn(i).getDataSize());
			m_file->WriteInt(m_TableHead->GetColmn(i).getFlog());
			m_file->WriteStr(m_TableHead->GetColmn(i).getStrForTableName());
			m_file->WriteStr(m_TableHead->GetColmn(i).getStrForColName());
		}
	}
	m_file->WriteInt(m_TableBody.GetLength());
	for (int i = 0; i < m_TableBody.GetLength(); i++)
	{
		m_file->WriteStr(m_TableBody.GetValue(m_TableBody.GetAvailableData(i+1)));
	}
	m_file->Close('o');
//	cout << GetTableName() << "表保存成功！" << endl; 
	return true;
}
//读取数据到文件中
bool MyTable::LoadData()
{
	m_file->Open('i');
	m_TableHead = new TableHead();
	string indexName="";
	string indexStrName = "";
	Column c;
	string str;
	
	int recordCount;
	m_pParent = m_file->ReadStr();
//	cout << m_pParent; 测试
 	int columnCount = m_file->ReadInt();
	
	for (int i = 0; i < columnCount; i++)
	{
		string columnName = m_file->ReadStr();
		c.setColName(columnName);
		c.setDataType((E_DATA_TYPE)(m_file->ReadInt()));
		c.setDataSize(m_file->ReadInt());
		c.setFlog(m_file->ReadInt());
		c.setStrForTableName(m_file->ReadStr());
		c.setStrForColName(m_file->ReadStr());
		if(c.getFlog() == 1) // 判断是否为主键
			indexName = c.getColName();
		else if (c.getFlog() == 3)
			indexStrName = c.getColName();
		m_TableHead->AddColumn(c);
	}
	
	recordCount =  m_file->ReadInt();
	for (int j = 0; j < recordCount; j++)
	{
		str = m_file->ReadStr();
		m_TableBody.Allocate(str);
	}
	if (indexName != "")
	{
		SetIndex(indexName);
	}
	if (indexStrName != "")
		SetStrIndex(indexStrName);
	m_bLoaded = true;
	m_file->Close('i');
	return true;
}

void MyTable::PrintTableHead()
{
	for (int i = 0; i < m_TableHead->GetColumnCount(); i++)
	{
		cout << left << setw(15) <<m_TableHead->GetColmn(i).getColName();
	}
	cout << endl;
}
bool MyTable::PrintTableHead(LList<string>& columnList,  LList<int>& columnPos)
{
	int pos;
	string columnName;
	columnList.setStart();
	int length = columnList.rightLength();

	columnList.setPos(0);
	columnList.getValue(columnName);
	if (columnName == "*")
	{
		for (int i = 0; i < m_TableHead->GetColumnCount(); i++)
		{
			columnPos.append(i);
			cout << left << setw(15) <<m_TableHead->GetColmn(i).getColName();
		}
		cout << endl;
		return true;
	}

	for (int i = 0; i < length; i++)
	{
		columnList.setPos(i);
		columnList.getValue(columnName);
		pos = IsTableColumn(columnName);
		if (pos >= 0)
		{
			columnPos.append(pos);
			cout << left << setw(15) << m_TableHead->GetColmn(pos).getColName();
		}
		else
		{
			
			cout << columnName << "列不存在！"  << "\007" << endl;
			return false;
		}
		columnList.next();
	}
	cout << endl;
	return true;
}
Column MyTable::GetColumn(const string& columnName) const
{
	Column temp;
	int i = 0;
	for (; i < m_TableHead->GetColumnCount(); i++)
	{
		if (m_TableHead->GetColmn(i).getColName() == columnName)
		{
			temp = m_TableHead->GetColmn(i);
			return temp;
		}
	}
	if (i >= m_TableHead->GetColumnCount())
	{
		cout << "没有找到相应的列！" << "\007" << endl;
	}
	return temp;
}