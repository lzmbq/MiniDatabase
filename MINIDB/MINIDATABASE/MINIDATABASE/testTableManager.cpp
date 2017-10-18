 //MINIDATABASE.cpp : 定义控制台应用程序的入口点。
//
//
//#include "stdafx.h"
//#include "TableManager.h"
//#include "string"
//#include "AVLTree.h"
//#include "Index.h"
//using namespace std;
//int _tmain(int argc, _TCHAR* argv[])
//{

//	// construst Head;
//	TableHead head;
//	Column column, column2, column3;
//	column.setColName("学号");
//	column.setDataSize(10);
//	column.setDataType(MY_LONG);
//	column.setFlog(1);
//
//	column2.setColName("年龄");
//	column2.setDataSize(3);
//	column2.setDataType(MY_INT);
//	
//	column3.setColName("姓名");
//	column3.setDataSize(20);
//	column3.setDataType(MY_PCHAR);
//
//	head.AddColumn(column);
//	head.AddColumn(column2);
//	head.AddColumn(column3);
//	
//	MyTable table(head,"student");
////	table.SetTableName("student");
//
//	
//
//
//	TableManager tm("StudentDB");
////	tm.selectData("greater",60321,"student");
//	tm.selectData("equal",60321,"student");
////
////	tm.createTable(table);
//	tm.setDataBaseName("StudentInfo");
//
//	string a[3];a[2]="wangyi";a[1]="20";a[0]="60320";
//	string b[3];b[2]="zhanglei";b[1]="20";b[0]="60326";
//	string c[3];c[2]="yuanlihao";c[1]="20";c[0]="60324";
//	string d[3];d[2]="xionghaichao";d[1]="19";d[0]="60321";
//	tm.insertData(a,"student");
//	tm.insertData(b,"student");
//	tm.insertData(c,"student");
//	tm.insertData(d,"student");
//	
//	
//	Index index;
//	table.SetIndex(&index,"学号");
//	index.A.print();
//
//	//table.Select(60326);
//	//table.Delete(60326);
//	table.Select("less",60326);
//
//	cout << "----------------------" << endl;
//	
//	table.Updata(60324,"年龄","5");
//	table.Select("equal",60324);
//	//table.Select("greater",60321);
//	index.A.print();
//	return 0;
//}
//
