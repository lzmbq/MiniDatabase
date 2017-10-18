//#ifndef TABLE_H_
//#define TABLE_H_
//#include "LList.h"
//#include "Column.h"
//#include <string>
//using namespace std;
//class Table
//{
//private:
//	LList<Column> m_pListColumn; // ����Ϣ�б�
//	string m_pStrTableName; // ����
//	int m_iColumnCount; // ����
//	int m_iAllColumnSize; // һ�е����ݵ��ܴ�С
////	LList<CIndex *> * m_pListIndex; // ����
//	int m_iRowCount; // ����
////	Matrix * m_pMatrix; // ���ݼ���
//	SimSpace<string> m_dbSet;  // �ҵ����ݼ���
////	Matrix::PMATRIX_COLUMNTYPE m_pMatrixColumnType; // ������
////	CFileRW* m_pFileRW; // ��д�ļ�����
////	bool m_bLoaded; // �Ƿ��Ѿ�װ��
////	LList<char *> * m_pListParentT; // �������б�
////	LList<char *> * m_pListChildrenT; // �ӱ����б�
////	CIndex * m_pPrimaryIndex; // ������
////	LList<CIndex *> * m_pListIndex; // ����
//public:
//	bool Insert(string record); // һ�����ݼ�¼��ָ��
////	bool Update(List<char *>*pStrColumnSet, List<char *>* pStrValueSet, char * pStrWhereSet) = 0;//�����ļ��� ����ֵ�ļ��� Where�Ӿ�
////	bool Delete(char * pStrWhereSet) ; // Where�Ӿ�
////	bool Select(char* pStrWhereSet) = 0;
//	bool Select(int i);
//	bool CreateTable(LList<Column> pListColumn) ; // �����Եļ���
////	bool AlterTable(List<Column *> * pListColumn) = 0;
////	bool DeleteTable();
//	LList<Column> GetColumnInfo() const;
//	bool SaveBody() const;
/////	bool IsPriKeyValueExist(Matrix::PMATRIX_ROW pMatrixRow) = 0; //BOOL����ʾ���ظ��е�����ֵ�Ƿ��Ѿ��͹�ȥ���ݵ�����ֵ�ظ�
////	bool IsReference(IOper * pChildTable, IOper * pParentTable) = 0;//�ú����ṩ�ж������е������Ƿ��Ѿ����ӱ��е�����������
////	bool CKConsistenc(Matrix::PMATRIX_ROW pMatrixRow, IOper * pParentTable) = 0;//�ú����ṩ�ж����������Ƿ��븸������ݱ���һ��
//	string GetTableName() const;
////	LList<char *>* GetParentList() = 0;//�ú����õ��������ĸ���
////	LList<char *>* GetChildList() = 0;
////	LList<int>* GetPrimaryKeyPos() = 0;//�ú����õ�ȫ�������������ڵ�λ��
////	LList<int>* GetForeignKeyPos(char * pStrTableName) = 0;
////	int KeySize(List<int>* listPos, Matrix::PMATRIX_ROW pMatrixRow) = 0;
////	bool InsertChildList(char * pChildTableName) = 0; //�ú������ڽ�һ���ӱ������뱾����ӱ���
////	void ClearChildList() = 0; //�ú�����������ӱ�
////	bool InsertParentList(char* pParentTableName) = 0; // ������
////	void ClearParentList() = 0; // �ú���������ո���
////	bool DeleteChildTable(char * pChildTableName) = 0; // �ú�������ɾ��һ���ӱ�
//};
//
//#endif