/********************************************************************
	created:	2008/06/15
	created:	15:6:2008   23:02
	modified:	
	filename: 	TableManager
	file ext:	h
	author:		
	
	purpose:	���ݿ������ɶԱ����ɾ��Ĳ������Լ����ݵ���ɾ���
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
	// ��ļ���
	AList<MyTable*>* m_DataBase;
	// ���ݿ�����
	string m_sDataBaseName;
	// �ļ���д��
	CFileRW* m_file;
	
	string path;
	/// <summary>
    /// ���ı��ļ��ж�ȡ���ݡ�
    /// </summary>
	/// <returns>�����Ƿ�ɹ�</returns>
	bool LoadTableLabels();

	/// <summary>
    /// �ͷ����б���ڴ�ռ䡣
    /// </summary>
	/// <returns>�����Ƿ�ɹ�</returns>
	bool Remove();
public:
	/// <summary>
    /// ���ݱ���������
    /// </summary>
	TableManager(const string& DBName){
		m_sDataBaseName = DBName;
		m_DataBase = new AList<MyTable*>();
		path = "data\\" + DBName + "\\";
		m_file = new CFileRW((path + DBName+".txt").c_str());
		//cout << path + DBName+".txt";  ����·���Ƿ���ȷ
		LoadTableLabels();
	}

	/// <summary>
    /// �ͷ����ݿ�ռ䡣
    /// </summary>
	~TableManager(){
		SaveTableLabels();
		Remove();
		delete m_file;
		delete m_DataBase;
	}

	/// <summary>
    /// �������ݿ������Ϣ��
    /// </summary>
	/// <returns>�����Ƿ�ɹ�</returns>
	bool SaveTableLabels() throw (const string);

	/// <summary>
    /// �������ݿ����ơ�
    /// </summary>
    /// <param name="name">���ݿ�����</param>
	/// <returns>�����Ƿ�ɹ�</returns>
	bool setDataBaseName(string name) throw (const string);

	/// <summary>
    /// ������ݿ����ơ�
    /// </summary>
	/// <returns>���ݿ�����</returns>
	string getDataBaseName() const throw (const string);

	/// <summary>
    /// ������������ݡ�
    /// </summary>
	/// <param name="tableName">����ı������</param>
	/// <returns>�����Ƿ�ɹ�</returns>
	bool saveData(const string & tableName) throw (const string);

	/// <summary>
    /// ������
    /// </summary>
	/// <param name="t">MyTable���ʵ��</param>
	/// <returns>�����Ƿ�ɹ�</returns>
	bool createTable(MyTable& t) throw (const string);

	/// <summary>
    /// ������
    /// </summary>
	/// <param name="tableName">�������������</param>
	/// <returns>�����Ƿ�ɹ�</returns>
	bool createTable(const string & tableName) throw (const string);

	/// <summary>
    /// ���ݱ�����ñ�
    /// </summary>
	/// <param name="tableName">��Ҫ��õı������</param>
	/// <param name="temp">��ñ�󱣴���temp��</param>
	/// <returns>�����Ƿ�ɹ�</returns>
	bool getTable(MyTable* &temp, const string & tableName) throw (const string);

	/// <summary>
    /// ��������������
    /// </summary>
	/// <param name="columnName">�������е�����</param>
	/// <param name="tableName">�����ñ������</param>
	/// <returns>�����Ƿ�ɹ�</returns>
	bool setPrimary(const string& columnName, const string & tableName) throw (const string);

	/// <summary>
    /// �������������
    /// </summary>
	/// <param name="columnName">�������е�����</param>
	/// <param name="tableName">�����ñ������</param>
	/// <param name="fColumnName">�������������ⲿ�е�����</param>
	/// <param name="fTableName">�������������ⲿ�������</param>
	/// <returns>�����Ƿ�ɹ�</returns>
	bool setForeign(const string& columnName, const string& fColumnName, const string & fTableName, const string & tableName) throw (const string);

	/// <summary>
    /// �鿴����Ϣ��
    /// </summary>
	/// <param name="tableName">���鿴�������</param>
	/// <returns>�����Ƿ�ɹ�</returns>
	bool describe(const string & tableName) throw (const string);

	/// <summary>
    /// �鿴����ϵ��
    /// </summary>
	/// <param name="tableName">���鿴�������</param>
	/// <returns>�����Ƿ�ɹ�</returns>
	bool getTableRelation(const string & tableName) throw (const string);

	/// <summary>
    /// ɾ���������
    /// </summary>
	/// <param name="tableName">��ɾ���������</param>
	/// <returns>�����Ƿ�ɹ�</returns>
	bool deleteTable(const string& tableName) throw (const string);

	/// <summary>
    /// �޸ı�����������С�
    /// </summary>
	/// <param name="columnName">Ҫ���ӵ��е�����</param>
	/// <param name="columnType">Ҫ���ӵ��е�����</param>
	/// <param name="tableName">���޸ı������</param>
	/// <returns>�����Ƿ�ɹ�</returns>
	bool alterTable(const string& columnName, const string& columnType, const string& tableName) throw (const string);

	/// <summary>
    /// ɾ���в�����
    /// </summary>
	/// <param name="columnName">��ɾ���е�����</param>
	/// <param name="tableName">�������</param>
	/// <returns>�����Ƿ�ɹ�</returns>
	bool dropTableColumn(const string& columnName, const string& tableName) throw (const string);

	/// <summary>
    /// �����¼������
    /// </summary>
	/// <param name="data">�����������</param>
	/// <param name="tableName">�������</param>
	/// <returns>�����Ƿ�ɹ�</returns>
	bool insertData(string data[], const string & tableName) throw (const string);

	/// <summary>
    /// ���Ҽ�¼������
    /// </summary>
	/// <param name="comp">��ؼ��ֱȽϵķ�ʽ</param>
	/// <param name="sql">���ҵĹؼ���</param>
	/// <param name="tableName">�������</param>
	/// <returns>�����Ƿ�ɹ�</returns>
	bool selectData(LList<string>& columnList, const string& comp,const int & sql,const string & tableName) throw (const string);

	/// <summary>
    /// ���Ҽ�¼������������������С�
    /// </summary>
	/// <param name="comp">��ؼ��ֱȽϵķ�ʽ</param>
	/// <param name="sql">���ҵĹؼ���</param>
	/// <param name="tableName">�������</param>
	/// <returns>�����Ƿ�ɹ�</returns>
	bool selectDataByDesc(LList<string>& columnList, const string& comp, const int & sql,const string & tableName) throw (const string);

	/// <summary>
    /// ���ұ������м�¼��
    /// </summary>
	/// <param name="tableName">�������</param>
	/// <returns>�����Ƿ�ɹ�</returns>
	bool selectData(LList<string>& columnList,const string & tableName) throw (const string);

	/// <summary>
    /// ���ұ��м�¼��
    /// </summary>
	/// <param name="column">��¼��ƥ����</param>
	/// <param name="tableName">�������</param>
	/// <returns>�����Ƿ�ɹ�</returns>
	bool selectData(LList<string>& columnList, const string& column, const string & tableName) throw (const string);
	
	/// <summary>
    /// ɾ����¼������
    /// </summary>
	/// <param name="comp">��ؼ��ֱȽϵķ�ʽ</param>
	/// <param name="sql">���ҵĹؼ���</param>
	/// <param name="tableName">�������</param>
	/// <returns>�����Ƿ�ɹ�</returns>
	bool deleteData(const string& comp, const int & sql,const string & tableName) throw (const string);

	/// <summary>
    /// �޸ļ�¼������
    /// </summary>
	/// <param name="comp">��ؼ��ֱȽϵķ�ʽ</param>
	/// <param name="sql">���ҵĹؼ���</param>
	/// <param name="tableName">�������</param>
	/// <returns>�����Ƿ�ɹ�</returns>
	bool updataData(int index, const string& columnName, const string& value, const string & tableName) throw (const string);

	/// <summary>
    /// ��������������
    /// </summary>
	/// <param name="columnName">�����õ�����</param>
	/// <param name="tableName">�������</param>
	/// <returns>�����Ƿ�ɹ�</returns>
	bool setIndex(const string & columnName, const string & tableName) throw (const string);
	
	/// <summary>
    /// �鿴���ݿ��еı�
    /// </summary>
	/// <returns>�����Ƿ�ɹ�</returns>
	bool showTables() throw (const string);
};	
#endif