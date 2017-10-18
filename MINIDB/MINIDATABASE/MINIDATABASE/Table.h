//#ifndef TABLE_H_
//#define TABLE_H_
//#include "LList.h"
//#include "Column.h"
//#include <string>
//using namespace std;
//class Table
//{
//private:
//	LList<Column> m_pListColumn; // 列信息列表
//	string m_pStrTableName; // 表名
//	int m_iColumnCount; // 列数
//	int m_iAllColumnSize; // 一行的数据的总大小
////	LList<CIndex *> * m_pListIndex; // 索引
//	int m_iRowCount; // 行数
////	Matrix * m_pMatrix; // 数据集合
//	SimSpace<string> m_dbSet;  // 我的数据集合
////	Matrix::PMATRIX_COLUMNTYPE m_pMatrixColumnType; // 列类型
////	CFileRW* m_pFileRW; // 读写文件对象
////	bool m_bLoaded; // 是否已经装载
////	LList<char *> * m_pListParentT; // 父表名列表
////	LList<char *> * m_pListChildrenT; // 子表名列表
////	CIndex * m_pPrimaryIndex; // 主索引
////	LList<CIndex *> * m_pListIndex; // 索引
//public:
//	bool Insert(string record); // 一行数据记录的指针
////	bool Update(List<char *>*pStrColumnSet, List<char *>* pStrValueSet, char * pStrWhereSet) = 0;//列名的集合 更改值的集合 Where子句
////	bool Delete(char * pStrWhereSet) ; // Where子句
////	bool Select(char* pStrWhereSet) = 0;
//	bool Select(int i);
//	bool CreateTable(LList<Column> pListColumn) ; // 列属性的集合
////	bool AlterTable(List<Column *> * pListColumn) = 0;
////	bool DeleteTable();
//	LList<Column> GetColumnInfo() const;
//	bool SaveBody() const;
/////	bool IsPriKeyValueExist(Matrix::PMATRIX_ROW pMatrixRow) = 0; //BOOL，表示返回该行的主键值是否已经和过去数据的主键值重复
////	bool IsReference(IOper * pChildTable, IOper * pParentTable) = 0;//该函数提供判读父表中的数据是否已经被子表中的数据所引用
////	bool CKConsistenc(Matrix::PMATRIX_ROW pMatrixRow, IOper * pParentTable) = 0;//该函数提供判读该行数据是否与父表的数据保持一致
//	string GetTableName() const;
////	LList<char *>* GetParentList() = 0;//该函数得到本表对象的父表
////	LList<char *>* GetChildList() = 0;
////	LList<int>* GetPrimaryKeyPos() = 0;//该函数得到全部主键的列所在的位置
////	LList<int>* GetForeignKeyPos(char * pStrTableName) = 0;
////	int KeySize(List<int>* listPos, Matrix::PMATRIX_ROW pMatrixRow) = 0;
////	bool InsertChildList(char * pChildTableName) = 0; //该函数用于将一个子表名插入本表的子表集合
////	void ClearChildList() = 0; //该函数用于清空子表
////	bool InsertParentList(char* pParentTableName) = 0; // 父表名
////	void ClearParentList() = 0; // 该函数用于清空父表
////	bool DeleteChildTable(char * pChildTableName) = 0; // 该函数用于删除一个子表
//};
//
//#endif